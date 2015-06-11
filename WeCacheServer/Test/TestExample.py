import sys
from PackReq import *

SVR_ADDR=("127.0.0.1", 8080)

def Test_Example():
	print "Test_Example..."

	CMD = 9998
	REQ = "Test_Example"
	TID = 12345

	ReqAndRsp(SVR_ADDR, CMD, REQ, TID)  
	print "_________________"

#########################################
if __name__ == '__main__':
	Test_Example()
