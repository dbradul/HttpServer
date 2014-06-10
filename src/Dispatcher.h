/*
 * Dispatcher.h
 *
 *  Created on: 06/04/2014
 *      Author: DB
 */

#ifndef DISPATCHER_H_
#define DISPATCHER_H_

#include "protocol/Request.h"
#include "protocol/Response.h"

class Dispatcher
{
    public:
        Dispatcher();
        virtual ~Dispatcher();

        void start();
        void stop();
        Request readRequest();
        bool writeResponse(Response response, int sessionId) const;
        int getSessionId() const;

    private:
        bool mbStarted;
        int mSocketDesc;
        int mSessionId;
};

#endif /* DISPATCHER_H_ */
