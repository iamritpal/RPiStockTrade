#include <iostream>
#include <cstring>
#include "curl.h"

Curl* Curl::m_pInstance = NULL;

Curl::Curl(){
    // init a multi stack
    multi_handle = curl_multi_init();
    if (multi_handle == NULL)
        throw Exception("Unable to initialize curl handler");
}

Curl* Curl::getInstance()
{
    if (!m_pInstance)           // Only allow one instance of class to be generated.
        m_pInstance = new Curl();
    return m_pInstance;
}

Curl::~Curl()
{
    int i;
    curl_multi_cleanup(multi_handle);

    /* Free the CURL handles */ 
    for (i=0; i<nmbHandles; i++)
        curl_easy_cleanup(handles[i]);
}

void Curl::init(void)
{
    nmbHandles = 0;
    still_running = 0;
}

void Curl::refresh()
{
    /* start some action by calling perform */
    curl_multi_perform(multi_handle, &still_running);
}

void Curl::AddGetRequest(const std::string &url)
{
    CURLcode res;

    if (nmbHandles < 10)
    {
        int i = nmbHandles;
        handles[i] = curl_easy_init();

        res = curl_easy_setopt(handles[i], CURLOPT_URL, url.c_str());
        if (res != CURLE_OK)
            throw Exception(res);

        res = curl_easy_setopt(handles[i], CURLOPT_SSL_VERIFYPEER, 0);
        if (res != CURLE_OK)
            throw Exception(res);

        // 301 redirect follow url
        res = curl_easy_setopt(handles[i], CURLOPT_FOLLOWLOCATION, 1); 
        if (res != CURLE_OK)
            throw Exception(res);

        // Progress bar not required
        res = curl_easy_setopt(handles[i], CURLOPT_NOPROGRESS, 1L);
        if (res != CURLE_OK)
            throw Exception(res);

        res = curl_easy_setopt(handles[i], CURLOPT_WRITEFUNCTION, write_data_cb);
        if (res != CURLE_OK)
            throw Exception(res);

        res = curl_easy_setopt(handles[i], CURLOPT_WRITEDATA, &m_data[i]);
        if (res != CURLE_OK)
            throw Exception(res);

        res = curl_easy_setopt(handles[i], CURLOPT_ENCODING, "");
        if (res != CURLE_OK)
            throw Exception(res);

        res = curl_easy_setopt(handles[i], CURLOPT_SSL_VERIFYHOST, 0);
        if (res != CURLE_OK)
            throw Exception(res);

        curl_multi_add_handle(multi_handle, handles[i]);

        // URL successfully added to curl
        nmbHandles++;
    }
}

int Curl::write_data_cb(char *data, size_t size, size_t nmemb, std::string *buffer)
{
    int result = 0;
    if (buffer != NULL) {
        buffer->append(data, size * nmemb);
        result = size * nmemb;
    }
    return result;
}

int Curl::isRunning(void)
{
    return(still_running);
}

void Curl::checkHandleStatus(void)
{
    while ((msg = curl_multi_info_read(multi_handle, &msgs_left)))
    {
        if (msg->msg == CURLMSG_DONE) 
        {
            int idx, found = 0;

            // Find out which handle this message is about
            for (idx=0; idx<nmbHandles; idx++) 
            {
                found = (msg->easy_handle == handles[idx]);
                if(found)
                    break;
            }
            std::cout << "Handle/url # " << idx  << " HTTP transfer completed with status " << curl_easy_strerror(msg->data.result) << std::endl;
        }
    }
}
