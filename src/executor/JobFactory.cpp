/*******************************************************************
 * JobFactory.cpp
 *
 *  @date: 2-8-2014
 *  @author: DB
 ******************************************************************/

#include "common/traceout.h"
#include "common/Utils.h"
#include "common/Config.h"
#include "executor/JobFactory.h"
#include "builder/Templater.h"
#include "builder/PageBuilder.h"
#include <memory>

using namespace std;


namespace HTTP
{

class JobRequestGET: public IJob
{
public:
    std::string execute()
    {
        TRC_INFO(0, "GET request for the path: %s", mPath.c_str());

        PageBuilder builder;

        std::string result;
        std::string URL = Config::getValueStr(Config::ROOT_DIR) + mPath;

        if (Utils::endsWith(URL, "/"))
        {
            std::vector<File> content = Utils::getDirContent(URL);
            HTMLDecorator<File> decorator;
            decorator.setURL(URL);

            result = builder.build(content, decorator);
        }

        else
        {
            std::vector<std::string> content = Utils::getFileContent(URL);
            HTMLDecorator<std::string> decorator;
            decorator.setURL(URL);

            result = builder.build(content, decorator);
        }

        return result;
    }

    JobRequestGET(const std::string& path)
    {
        mPath = path;
    }

private:
    std::string mPath;
};


//---------------------------------------------------------------------------------------
JobFactory::JobFactory()
//---------------------------------------------------------------------------------------
{
    TRC_DEBUG_FUNC_ENTER(0U, "");
    TRC_DEBUG_FUNC_EXIT (0U);
}

//---------------------------------------------------------------------------------------
JobFactory::~JobFactory()
//---------------------------------------------------------------------------------------
{
    TRC_DEBUG_FUNC_ENTER(0U, "");
    TRC_DEBUG_FUNC_EXIT (0U);
}

//---------------------------------------------------------------------------------------
IJob::Ptr JobFactory::createJob(Request::Type requestType, const std::string& url)
//---------------------------------------------------------------------------------------
{
    switch(requestType)
    {
    case Request::Type::GET:
        return make_unique<JobRequestGET>(url);

    default:
        throw runtime_error("Unsupported request method type");
    }
}

//---------------------------------------------------------------------------------------
Callback JobFactory::createOnFinishCallback(const Connection& connection, const int sessionId)
//---------------------------------------------------------------------------------------
{
    return [&connection, sessionId] (const std::string& result)
    {
        Response response;
        response.setResultCode  (Response::OK);
        response.setBody        (result);

        TRC_DEBUG(0, "Response constructed: %s", response.getStartLine().c_str());

        if( !connection.writeResponse(response, sessionId) )
        {
            TRC_ERROR(0U, "Failed sending response");
        }
    };
}

//---------------------------------------------------------------------------------------
Callback JobFactory::createOnErrorCallback(const Connection& connection, const int sessionId)
//---------------------------------------------------------------------------------------
{
    return [&connection, sessionId] (const std::string& result)
    {
        Templater templater     (Templater::PATH_ERROR);
        templater.setMacro      (Templater::MACROS_CONTENT, result);

        Response response;
        response.setResultCode  (Response::INTERNAL_SERVER_ERROR);
        response.setBody        (templater.generate());

        TRC_DEBUG(0U, "Response will be sent to a caller: %s", response.getStartLine().c_str());

        if( !connection.writeResponse(response, sessionId) )
        {
            TRC_ERROR(0U, "Failed responding");
        }
    };
}

}
