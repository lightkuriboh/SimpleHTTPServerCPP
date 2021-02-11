
# INSTALLATION  

#### SERVER  
```
$ chmod +x first_time_run.sh
$ ./first_time_run.sh
# Run
$ ./run.sh
```
* You may need to increase OpenFiles Limit (ulimit -n) to larger number (i.e. 20000) in local environment to handle more connections. 

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
* Multiple clients to connect to the server at the same time.  
* Supports HTTP/1.1.  
* Get the response by request type and endpoint.  
    * "GET /" : return ```index.html``` page.  
    * "GET /{some text file}" : return any pre-loaded files to the client.   
* Get files (image, text, ...)  
    * "GET /{fileName}": return that file to the client.  

# EXPLANATION 
* Maintains a file descriptor for listening socket called ```socketMaster```. The ```socketMaster``` is responsible for listening port ```PORT``` (```PORT = 2101``` by default).
   
* To monitor events on the file descriptors, I use ```epoll``` that is a data structure (Red-Black Tree) to monitor events on file descriptors.
 
* First, creates an ```epollContext``` with ```epoll_create()``` and registers ```socketMaster``` to the ```epollContext```.

* ```epoll_wait()``` is used to get the file descriptors that are ready for I/O.
   
* When there is any I/O event on the ```socketMaster```, that means there is a connection is coming.

* Then ```accept()``` to open another socket to deal with that connection and register it to the ```epollContext```.

* If an event is seen on the file descriptor other than ```socketMaster```, base on the type of event, it will handle it.
   * When an ```EPOLLIN``` event occurs, then there is a request, I will handle the request and send some response to the client via that corresponding socket.
   * When an ```EPOLLERR``` or ```EPOLLHUP``` event occurs, I will close that connection.

* When the server is starting up, I load some static ```HTML``` files (```JS``` too) to respond quickly.

* The server supports transferring files. If you open ```/about.html``` page, you can see the browser is loading ```about.css```, ```about.js``` and images.

* I used a Thread Pool to handle "heavy" request (may be transferring a file, search in database, ...).  \
  First the ```pool``` is created with ```X``` thread(s) as ```X``` workers, which are infinitely looking into a mutex-locked queue of tasks.  \
  Whenever a ```worker``` takes a task from the queue, that ```worker``` executes it.
  
* This ```event-driven``` architecture allows the server to handle many connections and requests efficiently.  
  
# PERFORMANCE TESTING  
```
$ ./wrk -t5 -c10000 -d30s http://127.0.0.1:2101  
# Testing with 10000 connections kept openned within 30s by 5 threads  
```    
