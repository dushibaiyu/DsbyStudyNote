select *
from t_kenpin_data_2 
--检索t_kenpin_data_2的所有值
select reg_opt ,reg_date from t_kenpin_data_2
--仅检索reg_opt, reg_date的值
/*
select 数据库查询语句。
用法 select 要查询的字段值 from 表名
从得到需要的数据
*/



select reg_opt AS 人员 ,reg_date AS 日期 from t_kenpin_data_2
--检索reg_opt和reg_date并设定别名为 人员和日期
/*
AS :设定别名。
用法：字段值 AS 别名
在字段值的表头显示别名，而且在语句中查询时，别名也可作为字段值
*/

select distinct reg_opt, reg_date from t_kenpin_data_2
--检索结果过滤reg_opt和reg_date同时重复的值
/*
distinct:不允许重复的，会过滤掉后面字段的所有重复值，包括NULL
*/

select * from t_kenpin_data_2 order by reg_opt, reg_date desc
--检索结果按照reg_opt和reg_date排序，reg_opt升序排序，reg_date降序排序
/*
order by :排序，根据后面的字段排序，默认为升序，在字段后加入desc为降序
*/
