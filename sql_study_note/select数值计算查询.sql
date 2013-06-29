select reg_date, reg_opt,SUM(a_qty)+SUM(b_qty) AS ALL, 
			SUM(a_qty) AS ALLA, 
			SUM(b_qty) AS  ALLB,
			ROUND(SUM(b_qty)/((SUM(a_qty)+SUM(b_qty))*0.01),2)||'%' AS BLU
from t_kenpin_data_2 group by reg_date, reg_opt  
having  1=1 and reg_date >= '2013-04-06 00:00:00+08'and reg_date <=  '2013-04-09 00:00:00+08' 
	ORDER BY  reg_date desc,reg_opt

/*
SUM()计算和，
sql支持+，-，*，/，数学运算
||在结果后面添加字符串
ROUND（浮点数，精确值）设定浮点数的精确值
注意：在*和/中，如果双方都为整型，则结果只保留整型，只有一方或双方都为浮点型才得到浮点值。


*/