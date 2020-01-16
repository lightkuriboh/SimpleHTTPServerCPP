
# INSTALLATION  

#### SERVER  


#### WRK (FOR PERFORMANCE TESTING)  
```
$ sudo apt-get install build-essential libssl-dev git -y
$ git clone https://github.com/wg/wrk.git wrk
$ cd wrk
$ sudo make
# move the executable to somewhere in your PATH, ex:
sudo cp wrk /usr/local/bin
```   

# FEATURES SUPPORTED  

# EXPLANATION  

# TESTING PERFORMANCE  
```
./wrk -t1 -c10000 -d30s --latency http://127.0.0.1:8080  
# Testing with 10000 connections kept openned within 30s by 1 thread  
```  



