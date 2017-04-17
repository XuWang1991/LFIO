## LFIO
LFIO is an implementation for inductive learning Datalog program from input and output.

Notice that LFIO could only run in LINUX system (We have test LFIO system in Fedora and Ubuntu, and it could run currently)

## Install
First off, you should install FLex (https://github.com/westes/flex/releases) and GNU Bison (http://www.gnu.org/software/bison/).
 
Running ```sudo yum install flex bison``` to install the above two software in Fedora or Centos. Running ```sudo apt-get install flex bison``` to install them in Ubuntu.

Also, you should install Git to clone all the files of LFIO from GitHub to your computer. You can run ```sudo yum install git``` in Fedora or Centos, or you can run ```sudo apt-get install git``` in Ubuntu. 

Then you could download all the files of LFIO and compile it.

```
git clone https://github.com/XuWang1991/LFIO.git
cd LFIO
make
```

## Get Started

After installing the LFIO successfully, you can use LFIO system to run some test examples which you can find in 
