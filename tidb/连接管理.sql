# 连接管理

## 查看连接
show processlist;
-- 其中id指的是session id。
## 杀死会话
kill tidb 1316; -- session_id
SELECT concat("kill tidb ",id,";")  from INFORMATION_SCHEMA.PROCESSLIST p where user='root'

## 查询慢sql
admin show slow top  10
select * from INFORMATION_SCHEMA.PROCESSLIST p 
