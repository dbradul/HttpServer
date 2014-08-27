/*
 * Dispatcher.cpp
 *
 *  Created on: 06/04/2014
 *      Author: DB
 */

#include "pthread.h"
#include "stdio.h"
#include "assert.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <unistd.h>
#include <exception>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#include "core/Connection.h"
#include "common/traceout.h"
#include "common/Config.h"
#include "protocol/Message.h"

namespace HTTP
{

//---------------------------------------------------------------------------------------
Connection::Connection()
      : mbStarted(false)
      , mSocketDesc(-1)
      , mSessionId(-1)
      , mPort(0)
{
   TRC_DEBUG_FUNC_ENTER(0U, "");
   TRC_DEBUG_FUNC_EXIT(0U);
}

//---------------------------------------------------------------------------------------
Connection::~Connection()
{
   TRC_DEBUG_FUNC_ENTER(0U, "");
   disconnect();
   TRC_DEBUG_FUNC_EXIT(0U);
}

//---------------------------------------------------------------------------------------
void Connection::connect()
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "");

   if (!mbStarted)
   {
      int sockoptval = 1;

      // Two socket address structures - One for the server itself and the other for client
      struct sockaddr_in serv_addr = { 0 };

      // Create socket of domain - Internet (IP) address, type - Stream based (TCP) and protocol unspecified
      // since it is only useful when underlying stack allows more than one protocol and we are choosing one.
      // 0 means choose the default protocol.
      mSocketDesc = socket(AF_INET, SOCK_STREAM, 0);

      // A valid descriptor is always a positive value
      if (mSocketDesc < 0)
      {
         TRC_ERROR(0U, "Failed creating socket");
      }

      // allow immediate reuse of the port
      else if (0 != setsockopt(mSocketDesc, SOL_SOCKET, SO_REUSEADDR, &sockoptval, sizeof(int)))
      {
         TRC_ERROR(0U, "Failed configuring socket");
      }

      else
      {
         // Fill server's settings
         serv_addr.sin_family = AF_INET;
         serv_addr.sin_addr.s_addr = INADDR_ANY;
         serv_addr.sin_port = htons(mPort);

         // Attach the server socket to a port.
         // TODO we should fail if the port is busy
         if (bind(mSocketDesc, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
         {
            TRC_ERROR(0U, "Binding has failed");
         }

         else if (0 != listen(mSocketDesc, 4))
         {
            TRC_ERROR(0U, "Listening has failed");
         }

         else
         {
            mbStarted = true;
         }

         if (!mbStarted)
         {

            //TODO: meaningful message
            throw std::exception();
         }
      }
   }

   TRC_DEBUG_FUNC_EXIT(0U);
}

//---------------------------------------------------------------------------------------
void Connection::disconnect()
//---------------------------------------------------------------------------------------
{
   close(mSocketDesc);
   mbStarted = false;
}

/*
 * Blocks until message is complete
 */
//---------------------------------------------------------------------------------------
void Connection::readRequest(Request& request)
//---------------------------------------------------------------------------------------
{
   struct sockaddr client_addr = { 0 };
   socklen_t size = sizeof(client_addr);
   int connDesc = -1;
   mSessionId = -1;
   bool bMessageCompleted = false;

   TRC_INFO(0U, "Waiting for connection...");

   // Server blocks on this call until a client tries to establish connection.
   // When a connection is established, it returns a 'connected socket descriptor' different
   // from the one created earlier.
   while (!bMessageCompleted && -1 != (connDesc = accept(mSocketDesc, (struct sockaddr *) &client_addr, &size)))
   {
      TRC_INFO(0U, "Connected: desc=%d", connDesc);

      char chunk[1024] = { 0 };

      // The new descriptor can be simply read from / written up just like a normal file descriptor
      int nbytes = 0;
      std::string message;

      // read until message delimiter is found
      while (!bMessageCompleted && (nbytes = read(connDesc, chunk, sizeof(chunk) - 1)) > 0)
      {
         TRC_INFO(0U, "Received: %d bytes", nbytes);
         TRC_INFO(0U, "Received data: %s", chunk);

         message += chunk;
         std::size_t end_idx = message.find(Message::HEADER_BODY_DELIM);

         if (end_idx != std::string::npos)
         {
            message.resize(end_idx + 1);
            request.parse(message);
            request.setValid(true);
            request.setSessionId(connDesc);
            bMessageCompleted = true;
            mSessionId = connDesc;
         }
      }
   }

   return;
}

//---------------------------------------------------------------------------------------
bool Connection::writeResponse(const Response& response, int sessionId) const
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "Response='%s', sessionId=%d", response.toString().c_str(), sessionId);
   bool bResult = true;

   int nbytes = response.toString().size();

   TRC_INFO(0U, "Sending response back to client.");
   if (nbytes != write(sessionId, response.toString().c_str(), nbytes))
   {
      bResult = false;
   }

   TRC_DEBUG_FUNC_EXIT(0U);

   return bResult;
}

//---------------------------------------------------------------------------------------
int Connection::getSessionId() const
//---------------------------------------------------------------------------------------
{
   return mSessionId;
}

//---------------------------------------------------------------------------------------
void Connection::setPort(unsigned int port)
//---------------------------------------------------------------------------------------
{
   mPort = port;
}

}
