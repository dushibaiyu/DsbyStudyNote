select reg_date, reg_opt,ALLA+ALLB AS ALL ,ALLB,ALLA, ROUND(ALLB/((ALLA+ALLB)*0.01),2)||'%' AS B
from (select reg_date, reg_opt, SUM(a_qty) AS ALLA, SUM(b_qty) AS  ALLB
	from t_kenpin_data_2 group by reg_date, reg_opt
	having  reg_date = '2013-04-06 00:00:00+08') as foo

/*
	在查询结果中查询，可以form（select 语句）as 别名
*/