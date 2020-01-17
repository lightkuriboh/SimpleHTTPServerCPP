
# INSTALLATION  

#### SERVER  
```
$ chmod +x install.sh
$ ./install.sh
# Run
$ ./build/DTLMiniProject
```

#### WRK (FOR PERFORMANCE TESTING)  
```
$ sudo apt-get install build-essential libssl-dev git -y
$ git clone https://github.com/wg/wrk.git wrk
$ cd wrk
$ sudo make
# move the executable to somewhere in your PATH, ex:
$ sudo cp wrk /usr/local/bin
```   

# FEATURES SUPPORTED  
* Multiple clients to connect to the server at the same time  
* Supports HTTP/1.1 (persistent connection)  
* Get the response by request type and endpoint  
    * "GET /" : return home page  
    * "GET /about" : return about page   

# EXPLANATION
```  
* I maintained a file descriptor for listening socket called socketMaster. The socketMaster is responsible for listening port PORT (PORT = 2101 for default).
   
* To monitor events on the file descriptors, I used epoll, a data structure used to monitor events on file descriptors (the Red-Black Tree is used).
 
* First, I created an epollContext with epoll_create() and I register socketMaster to the epollContext.

* I use epoll_wait() to get the file descriptors that are ready for I/O.
   
* When there is any I/O event on the socketMaster, that means there is a connection is coming.

* Then I accept() to open another socket to deal with that connection and register it to the epollContext.

* If an event is seen on the file descriptor other than socketMaster, base on the type of event, I will handle it.
   * When an EPOLLIN event occurs, then there is a request, I will handle that request and send some response to the client via that corresponding socket.
   * When an EPOLLERR or EPOLLHUP event occurs, I will close that connection.

* When the server is starting up, I load static HTML files to respond based on the request's method and endpoint.
```  


# TESTING PERFORMANCE  
```
$ ./wrk -t1 -c10000 -d30s http://127.0.0.1:2101  
# Testing with 10000 connections kept openned within 30s by 1 thread  
```  
* To test the performance on pure requests only (only send back "HelloWorld"), pass "true" as parameter for MyServer's constructor in "main.cpp".  



