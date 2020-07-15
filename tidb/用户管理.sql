-- 1 用户管理
-- 1.1 用户创建
create user 'test1'@'%' identified by 'xxx';

-- 修改密码

set password for 'test1'@'%' = 'yyy';
or
alter user 'test1'@'%' identified by 'zzz';

-- 删除用户
drop user 'test1'@'%';

-- 1.2 授权
-- 授予test库的select权限
grant select on test.* to 'test1'@'%';

-- 授予所有权限
grant all privileges on test.* to 'test1'@'%';

-- 收回权限
revoke all privileges on  test.* from 'test1'@'%';

-- 查看权限
show grants for 'test1'@'%'

-- 需要刷新下内存中的权限
flush privileges;

mysql.user：用户账户，全局权限
mysql.db：数据库级别的权限
mysql.tables_priv：表级别的权限
mysql.columns_priv：列级别的权限，当前暂不支持




