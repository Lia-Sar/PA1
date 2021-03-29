#include <iostream>
#include <cstring>
#include <string>

// Function prototypes
bool checkValidProtocol(const std::string&);
bool checkValidDomain(const std::string&);
bool checkFilePath(const std::string&);
bool findElement(std::string, std::string);
bool is_digits(const std::string&);

int main()
{
   // flag for whether to repeat or stop the loop
   int flag = 0;

   // loops until user enters a URL
   while (flag == 0)
   {
      std::string line = " ",
         url = " ",
         protocol = " ",
         domain = " ",
         domainName = " ",
         port = " ",
         filepath = " ",
         path = " ",
         parameter = " ";

      bool validURL = true,
         validProtocol = true,
         validDomain = true,
         validPort = true,
         validPath = true,
         validParam = true,
         protoExists = true,
         domainExists = true,
         pathExists = true,
         portExists = false,
         paramExists = false;

      int port_num = 0;

      // prompt for url
      std::cout << "Enter the URL: ";
      std::cin >> line;

      // verify that the protocol exists
      if (findElement(line, "://") == true)
      {
         protocol = line.substr(0, line.find("://"));

         // check for valid protocol
         if (checkValidProtocol(protocol) == false)
         {
            if (protocol == "")
            {
               protoExists = false;
            }
            validProtocol = false;
            validURL = false;
         }
         // remove protocol component from string
         line.erase(0, protocol.length() + 3);
      }
      // protocol does not exist
      else
      {
         protoExists = false;
      }

      // domain is followed by a port 
      if (findElement(line, ":") == true)
      {
         portExists = true;                            // port exists
         domainName = line.substr(0, line.find(":"));  // get full domain name

         // verify there is a top-level domain
         if (findElement(domainName, ".") == true)
         {
            // get top-level domain from domain name
            domain = domainName.substr(domainName.find_last_of("."), domainName.length() - 1);

            // check for valid domain
            if (checkValidDomain(domain) == false)
            {
               if (domain == "")
               {
                  domainExists = false;
               }
               validDomain = false;
               validURL = false;
            }
         }
         // top-level domain does not exist
         else
         {
            domainExists = false;
            validDomain = false;
         }

         line.erase(0, domainName.length() + 1);
      }
      // domain is followed by the filepath
      else if (findElement(line, "/") == true)
      {
         domainName = line.substr(0, line.find("/"));    // get full domain name

         // verify there is a top-level domain
         if (findElement(domainName, ".") == true)
         {
            // get top-level domain from domain name
            domain = domainName.substr(domainName.find_last_of("."), domainName.length() - 1);

            // check for valid domain
            if (checkValidDomain(domain) == false)
            {
               if (domain == "")
               {
                  domainExists = false;
               }
               validDomain = false;
               validURL = false;
            }
         }
         // top-level domain does not exist
         else
         {
            domainExists = false;
            validDomain = false;
         }
         line.erase(0, domainName.length() + 1);      // remove domain name component from string
      }
      // domain name does not exist
      else
      {
         domainExists = false;
      }

      // port exists
      if (portExists == true)
      {
         port = line.substr(0, line.find("/"));    // obtain port
         if (port == "")
         {
            portExists = false;
         }
         // validate the port entry is an int
         else if (is_digits(port) == true)
         {
            port_num = stoi(port);
            // verify valid port number
            if (port_num < 1 || port_num > 65535)
            {
               std::cout << port_num << std::endl;
               validPort = false;
               validURL = false;
            }
         }
         // port entry is not an int
         else
         {
            validPort = false;
         }
         line.erase(0, port.length());       // remove port component from string
      }

      // filepath is followed by parameters
      if (findElement(line, "?") == true)
      {
         paramExists = true;
         filepath = line.substr(0, line.find("?"));   // get filepath

         // verify filepath ends with either .html or .htm
         if (findElement(filepath, ".") == true)
         {
            path = filepath.substr(filepath.find("."), filepath.length() - 1);
            if (checkFilePath(path) == false)
            {
               if (path == "")
               {
                  pathExists = false;
               }
               validPath = false;
               validURL = false;
            }
         }
         // invalid path
         else
         {
            pathExists = false;
            validPath = false;
         }
         line.erase(0, filepath.length() + 1);
      }
      // no parameters 
      else
      {
         filepath = line.substr(0, line.length());      // get filepath
         // verify filepath ends with either .html or .htm
         if (findElement(filepath, ".") == true)
         {
            path = filepath.substr(filepath.find("."), filepath.length() - 1);
            if (checkFilePath(path) == false)
            {
               if (path == "")
               {
                  pathExists = false;
               }
               validPath = false;
               validURL = false;
            }
         }
         // invalid path
         else
         {
            pathExists = false;
            validPath = false;
         }
         line.erase(0, filepath.length() - 1);
      }

      // obtain parameters if it exists
      if (paramExists == true)
      {
         parameter = line.substr(0, line.length());
      }

      // return back to the prompt if any required URL components don't exist
      if (pathExists == false || protoExists == false || domainExists == false)
      {
         std::cout << "Invalid input. Try again" << std::endl;
      }
      else
      {
         flag = 1;
         // display message for when all URL components are valid
         if (validURL == true)
         {
            std::cout << "Protocol:    " + protocol << std::endl;
            std::cout << "Domain:      " + domainName << std::endl;
            if (portExists == true)
            {
               std::cout << "Port:        " + port << std::endl;
            }
            std::cout << "File path:   " + filepath << std::endl;
            if (paramExists == true)
            {
               std::cout << "Parameters:  " + parameter << std::endl;
            }
         }
         // display error message for when there is at least one invalid URL component
         else
         {
            std::cout << "Invalid URL with following erroneous components:" << std::endl;
            if (validProtocol == false)
            {
               std::cout << "Protocol:    " + protocol + " is not a valid protocol" << std::endl;
            }
            if (validDomain == false)
            {
               std::cout << "Domain:      " + domain + " is an invalid domain name." << std::endl;
            }
            if (validPort == false)
            {
               std::cout << "Port:        port number must be between 1 and 65535" << std::endl;
            }
            if (validPath == false)
            {
               std::cout << "File path:   " + path + " is an invalid file path" << std::endl;
            }
         }

      }
   }
   return 0;
}

// verify protocol is valid
bool checkValidProtocol(const std::string& protocol)
{
   if (protocol != "https" && protocol != "http" && protocol != "ftp" && protocol != "ftps")
   {
      return false;
   }
   else
   {
      return true;
   }
}

// verify domain is valid
bool checkValidDomain(const std::string& domain)
{
   if (domain != ".com" && domain != ".net" && domain != ".edu" && domain != ".biz" && domain != ".gov")
   {
      return false;
   }
   else
   {
      return true;
   }
}

// verify path is valid
bool checkFilePath(const std::string& path)
{
   if (path != ".html" && path != ".htm")
   {
      return false;
   }
   else
   {
      return true;
   }
}

// sees if a substring exists in a certain string
bool findElement(std::string url, std::string substring)
{
   if (url.find(substring) != std::string::npos)
   {
      return true;
   }
   else
   {
      return false;
   }
}
// verifies that the string has all integer values
bool is_digits(const std::string& str)
{
   return str.find_first_not_of("0123456789") == std::string::npos;
}
