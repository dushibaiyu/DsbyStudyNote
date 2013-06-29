select * from t_kenpin_data_2
where a_qty > 20
--查询a_qty字段所有大于20的值
select * from t_kenpin_data_2
where a_qty > 20 AND a_qty <30
--查询a_qty字段所有大于20的值且小于30的值
select * from t_kenpin_data_2
where a_qty < 30 OR b_qty >0
--查询a_qty字段所有小于30或者b_qty字段大于20的值
/*
where：查询条件
用法 where 表达式
多个表达式用 与(AND) 和 或(OR) 连接
AND：多个表达式的值都必须满足
OR ：满足其中一个表达式即可
*/

select * from t_kenpin_data_2
where a_qty between 20 and 30
--查找a_qty介于20和30之间的值
select * from t_kenpin_data_2
where a_qty in(20,30,60,15)
--查找a_qty为20，30，60，15其中之一的值
/*
between and :在某个范围查询
用法 where 字段值 between A and B ，查找介于A和B之间的值，等价于 where 字段值>= A AND 字段值 <= B

in ：在孤立值集合中查询
用法 where 字段值 in (孤立值集合)
	例：where A in(b,c,d,e,···)等价于 where A=b or a=c or a=d or a=e or·······
*/

select * from m_opt
where pwd is not NULL
--检索pwd不为空的值
/*
is not NULL ：不为空。
is NULL ：为空
	（注意：好像在postgreSQL中，不存在空值）
*/
