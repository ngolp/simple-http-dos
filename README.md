# simple-http-dos

## General Information
1. This project is a self-motivated extension of an HTTP client/server project from my computer networks course (CS 3516).
2. The HTTP client and server both function on their own, but the goal of this extension (DOS demonstration) was to interrupt this function via HTTP flood and further my understanding of simple network vulnerabilities along the way.
3. To achieve this, simple_http_client.c has been modified into dos_attacker.c which will cause HTTP flooding with endless HTTP GET requests.
4. This project is made for educational purposes only. Do NOT use it on anything but your own servers.

## Getting Started
1. Download the files from this repository (dos_attacker.c, makefile, simple_http_client.c, simple_http_server.c, and TMDG.html)
2. Use the makefile to easily compile using the following command:

   _make all_

    ![image](https://github.com/user-attachments/assets/e4cea051-c71e-4ccd-b0eb-17c7823d5029)


3. Similarly, the object files and executables may be cleaned using the following command:

   _make clean_

4. For the makefile commands (make all and make clean) to work properly along with the given TMDG.html file (or any file being read by the server) to be read properly, ensure that the downloaded files are located within the same directory.

5. It is also important to note that the files are meant to be run within a Linux environment (i.e. makefile uses "rm" instead of "del" for "make clean", certain #include statements aren't valid in Windows, etc).

## One-click DoS attack guide

1. Ensure you're in the directory with run_dos_attack.sh
2. Ensure run_dos_attack.sh is in the directory with all source code files
3. Edit run_dos_attack.sh's TARGET variable: `TARGET=your-target-server-dot-com.com`
4. Make the script executable: run
       `chmod +x run_dos_attack.sh`
   in the terminal
6. Run
   `./run_dos_attack.sh`
   in the terminal
7. After you're done, stop all processes with
   `pkill http_server`


## Starting the Server

1. In a terminal, the HTTP server can be started by running a command in the following format:

   _./http_server <server_port>_

    Note:
    - The <server_port> is the port number the server will be listening on.
    - This should preferably be over 5000 to be safe since lower ports may be reserved for other tasks.

    ![image](https://github.com/user-attachments/assets/993cc864-bf34-498e-bf5a-bf64dc3bad5a)

2. The server will now be listening for requests on the desired port.

## Using the Client

1. With the server now listening for requests, open a second terminal and use the client to send an HTTP GET request for TMDG.html using a command in the following format:

   _./http_client <-options> <server_url> <server_port>_

   Note:
   - The <-options> space is for the -p flag, which will also display the RTT of connecting to the server in milliseconds.
   - The <server_port> space is for the server port number (equivalent to that of the running HTTP server, or 80 for any other HTTP usage).
   - My setup is hosted on the private WPI Linux server, which is why my <server_url> will be linux.wpi.edu/TMDG.html.

    ![image](https://github.com/user-attachments/assets/4f3485a1-0e1f-41ff-94f0-1b7943a974d7)

2. If successful, a new file (index.html) will be created in the current working directory containing the contents of the HTTP response (I requested TMDG.html in this case).

    ![image](https://github.com/user-attachments/assets/027f2f0b-9141-4483-bf9d-5cc342561366)


    ![image](https://github.com/user-attachments/assets/2462eb3f-cdd7-415a-b3aa-86edd249f993)

   The file is very long, so only the first piece is shown in the above screenshot.

3. The server will also display a message in its terminal.

    ![image](https://github.com/user-attachments/assets/7b712085-5e4c-4d0a-a364-b9f2f83c7639)

## Performing the DOS Attack

1. With the server running, a new terminal may be opened for the DOS attacker (three terminals in total with one for the server, one for the client, and now one for the DOS attacker).
  
2. The DOS attacker can be started in its terminal with the following command:

   _./dos_client <server_url> <server_port>_

   Note that <server_url> and <server_port> share the same meaning as with the HTTP client (see above section "Using the Client").
   
    ![image](https://github.com/user-attachments/assets/6d8127d0-86c2-4b95-9399-5f9253a0a74b)

4. The DOS attacker will now endlessly send HTTP GET requests for TMDG.html. The server will be able to keep up with the HTTP flood for a short moment but will freeze soon after.

    ![image](https://github.com/user-attachments/assets/82da6eb1-f90a-4e8b-a569-09b5761b48f7)

5. Once the HTTP server is frozen (stops displaying messages), that means the HTTP flood attack is working.

6. In the client's terminal, the steps from the above section "Using the Client" can now be repeated.

    ![image](https://github.com/user-attachments/assets/28a46fec-5036-4476-b738-a10941bae574)

7. Notice how this time, the client will not receive a response as the server is under attack (hence denial of service).

## Authors
 - Nicholas Golparvar
 - Matvey Shestopalov (implemented forking logic and run_dos_attack.sh)
