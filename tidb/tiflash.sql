##设置tiflash复制
alter table dim.dim_worker_info_df set tiflash replica 1;

##删除复制
alter table dim.dim_worker_info_df set tiflash replica 0;

##查看复制进度
select * from information_schema.tiflash_replica where table_schema = 'dim' and table_name = 'dim_worker_info_df'

#统计人员签到方向
#tiflash 8K内存，73ms
set @@session.tidb_isolation_read_engines='tikv,tiflash'
explain analyze select a.nation ,count(1) from dim.dim_worker_info_df a group by a.nation 

#tikv 8K内存，429ms
set @@session.tidb_isolation_read_engines='tikv'
explain analyze select  a.nation,count(1) from dim.dim_worker_info_df a group by a.nation 

#join中的运用
explain select a.*,b.birth_place from dwd.dwd_worker_attendance_day_df a
inner join dim.dim_worker_info_df b on a.worker_id = b.worker_id 



