from Common import *

def PackReq(cmd, str_data, tid):
	size=len(str_data)
	send_buf=PackHead(cmd, size, tid, 0)
	send_buf += str_data
	return send_buf

def ReqAndRsp(SVR_ADDR, CMD, REQ, TID):
	send_buf=PackReq(CMD, REQ, TID)
	print ("[REQ:cmd=%d,body_size=%d,tid=%d]\n%s" %(CMD, len(send_buf), TID, REQ))
	recv_buf = SendAndRecvData(SVR_ADDR, send_buf)

	MAGIC_,RET_,BODY_SIZE_,CMD_,TID_ = struct.unpack("!4s3i1q", recv_buf[0:24]);
	RSP=recv_buf[24:]
	print("[RSP:magic=%s,ret=%d,body_size=%d,cmd=%d,tid=%ld]\n%s" %(MAGIC_, RET_, BODY_SIZE_, CMD_, TID_, RSP))


