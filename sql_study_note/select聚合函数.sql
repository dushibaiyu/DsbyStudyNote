select max(reg_opt) from t_kenpin_data_2
--查询表中reg_opt的最大值
select count(*) from t_kenpin_data_2
--查询表中所有记录的个数

/*
聚合函数：多行返回一个值，通常用来统计分组信息。聚合函数是多行函数（即多行返回一个值）。

聚合函数：
	max() ：求最大值
	min() ：求最小值
	avg() ：求平均数
	count() ：求个数
		count(*)：求表中所有记录的个数（行数）。
		count(字段名)：求字段值的非空记录个数（行数），重复记录也算。
		count(distinct 字段名)：求字段不重复且不为空的个数（行数）。
*/