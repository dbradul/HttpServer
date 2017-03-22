/*******************************************************************
 *  IJob.h
 *
 *  @date: 28-7-2014
 *  @author: DB
 ******************************************************************/

#ifndef IJOB_H_
#define IJOB_H_

#include <functional>
#include <string>
#include <memory>

typedef std::function<void(const std::string&)> Callback;

class IJob
{
public:

    typedef std::unique_ptr<IJob> Ptr;

    enum Type
    {
        REGULAR,
        DUMMY_TERMINATE
    };

    IJob();
    explicit IJob(Type type);
    virtual ~IJob();

    virtual std::string execute() = 0;

    Type getType() const;

    void setOnFinishCallback(const Callback& callback);
    void setOnErrorCallback(const Callback& callback);

    Callback onFinishCallback;
    Callback onErrorCallback;

private:
    Type mType;
};


#endif /* IJOB_H_ */
