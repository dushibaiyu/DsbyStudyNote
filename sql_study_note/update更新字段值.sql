update t_kenpin_data_2 set ctnno='' where ctnno='0'
--更新数据

/*
	update 表名 set 字段
	where 条件表达式
	
	更新多个用“,”隔开，where 用或（or）或与（and）
*/

update m_opt set tel = '1', mail = '2'
where pwd = '' OR r_1 = '0'