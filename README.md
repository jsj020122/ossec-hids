OSSEC v3.1.0 Copyright (C) 2018 Trend Micro Inc.

# Information about OSSEC 

OSSEC is a full platform to monitor and control your systems. It mixes together 
all the aspects of HIDS (host-based intrusion detection), log monitoring and 
SIM/SIEM together in a simple, powerful and open source solution.

Visit our website for the latest information.  [ossec.github.io](http://ossec.github.io)

PS:
这个技术用的很一般，进程都是快照，网络都是netstat，分析文本日志，分析windows EventLog，快照主要的注册表项。这个项目的重点应该是规则和策略可以参考
具体目录  /etc中的规则  和 src\rootcheck\db中监控的具体部分


## Current Releases 

The current stable releases are available on the ossec website. 

* Releases can be downloaded from: [Downloads](http://ossec.github.io/downloads.html)
* Release documentation is available at: [docs](http://ossec.github.io/docs/)

## Development ##

The development version is hosted on GitHub and just a simple git clone away. 

[![Build Status](https://travis-ci.org/ossec/ossec-hids.svg?branch=master)](https://travis-ci.org/ossec/ossec-hids)
[![Coverity Scan Build Status](https://scan.coverity.com/projects/1847/badge.svg)](https://scan.coverity.com/projects/1847)


## Credits and Thanks ##

* OSSEC comes with a modified version of zlib and a small part 
  of openssl (sha1 and blowfish libraries)
* This product includes software developed by the OpenSSL Project
  for use in the OpenSSL Toolkit (http://www.openssl.org/)
* This product includes cryptographic software written by Eric 
  Young (eay@cryptsoft.com)
* This product include software developed by the zlib project 
  (Jean-loup Gailly and Mark Adler)
* This product include software developed by the cJSON project 
  (Dave Gamble)


