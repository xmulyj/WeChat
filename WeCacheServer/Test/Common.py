import sys
import socket
import time
import struct
from ctypes import c_longlong as longlong

def PackHead(cmd, body_size, tid, ret):
	MAGIC_NUM="PACK"
	tid_=longlong(tid)
	head=struct.pack("!4s3i1q",MAGIC_NUM, ret, body_size, cmd, tid_.value)
	return head

def SendData(svr_addr, data):
	sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	sock.connect(svr_addr)
	sock.send(data)
	print "send data finished,go to sleep 2s"
	time.sleep(2)
	sock.close()

def SendAndRecvData(svr_addr, data):
	sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	sock.connect(svr_addr)
	sock.send(data)
	recv_data = sock.recv(65536)
	sock.close()
	return recv_data

