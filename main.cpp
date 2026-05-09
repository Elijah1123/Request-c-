#include <iostream>
#include <string>
#include <curl/curl.h>

// Callback function to handle the incoming data stream
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main() {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init(); // Initialize the opaque data structure
    if(curl) {
        // Set the target URL bits
        curl_easy_setopt(curl, CURLOPT_URL, "https://www.google.com");

        // Pass a pointer to our string to the handle's internal state
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // Perform the transfer (the handle executes its state machine)
        res = curl_easy_perform(curl);

        if(res == CURLE_OK) {
            std::cout << "Data received. Size: " << readBuffer.size() << " bytes." << std::endl;
        }

        // Clean up the memory bits
        curl_easy_cleanup(curl);
    }
    return 0;
}