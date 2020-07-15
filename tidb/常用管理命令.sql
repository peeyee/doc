-- 常用管理命令

-- 查看某些参数

show variables  like '%stat%';

-- 查看全局参数
SHOW [GLOBAL|SESSION] VARIABLES;

show global variables like 'tidb%'