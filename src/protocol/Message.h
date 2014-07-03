/*******************************************************************
 * Message.h
 *
 *  @date: 30 квіт. 2014
 *  @author: DB
 ******************************************************************/

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <string>

class Message
{
    public:
        Message();
        virtual ~Message();

        const std::string& getRawMessage() const;

        static const std::string MESSAGE_HEADER_BODY_DELIMITER;
        static const std::string MESSAGE_HEADER_FIRST_FIELD_ENTRIES_DELIMITER;
        static const std::string MESSAGE_HEADER_FIELD_DELIMITER;
        static const std::string MESSAGE_HEADER_FIELD_NAME_DELIMITER;

    protected:
        std::string mRawMessage;
};

#endif /* MESSAGE_H_ */
