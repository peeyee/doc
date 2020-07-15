-- 执行计划

trace format='row' SELECT * FROM benchmark.sbtest1 s ;


-- 逻辑执行计划
-- 使用统计信息，估计的执行计划
explain select * from benchmark.sbtest1 s ;


-- 物理执行计划
explain analyze select * from benchmark.sbtest1 s ;


-- 查看table的统计信息
use benchmark;
show table status like '%sbtest1%';