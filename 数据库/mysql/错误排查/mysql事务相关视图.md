# 事务相关视图

## 会话

```sql
# 会话查询
select * from information_schema.processlist p 
where p.command = 'Query'
order by time desc
```

## 锁

```shell
# 5.7
select * from information_schema.innodb_locks;
select * from information_schema.innodb_lock_waits;

# 8.0
select * from performance_schema.data_locks dl; 
select * from performance_schema.data_lock_waits dlw; 
```

## 事务

```shell
# 事务信息视图
SELECT * FROM information_schema.innodb_trx;
```

