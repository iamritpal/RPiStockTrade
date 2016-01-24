#ifndef CURL_H
#define CURL_H

#include <string>
#include <map>
#include <stdexcept>
#include <cstdlib>
#include <curl/curl.h>

class Curl
{
    public:
        
        class Exception : public std::runtime_error     // Exception is used for curl errors
        {
        public:
            Exception(std::string const& message): std::runtime_error(message) {}
            Exception(CURLcode error): std::runtime_error(curl_easy_strerror(error)) {}
        };

        ~Curl();
        void init();
        void refresh();
        int isRunning();
        static int write_data_cb(char *data, size_t size, size_t nmemb, std::string *buffer);
        void AddGetRequest(const std::string &url);
        void checkHandleStatus(void);
        int still_running;
        int nmbHandles;
        std::string m_data[10];
        std::string urls[10];
        Curl* getInstance();
        static Curl* m_pInstance;

    private:
        Curl();
        Curl(const Curl &);         // No compiler-generated copy constructor
        CURL* handles[10];
        CURLM *multi_handle;
        CURLMsg *msg;               // For picking up messages with the transfer status        
        int msgs_left;              // how many messages are left
};

#endif