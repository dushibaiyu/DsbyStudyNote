select reg_opt, reg_date, AVG(a_qty) from t_kenpin_data_2
group by reg_opt,reg_date
--按照reg_opt和reg_date分组，先按照reg_opt分组，如果相同则按照reg_date分组
/*
group by :按照表中的字段分成不同的组。
用法 ：group by 字段集合
	例：group by a,b,c 
		先按照a分组，如果a相同则按照b分组，如果b相同则按照c分组，最后统计的是最小分组的信息。

group by 后面不可跟where语句，对分组信息进行过滤用having
一般group by和聚合函数一起使用。
*/

select reg_opt, reg_date from t_kenpin_data_2
group by reg_opt,reg_date 
having reg_opt < '50'
--按照reg_opt和reg_date分组，并过滤分组后reg_opt大于和等于'50'的值

/*
having ：对分组后数据进行过滤（条件查询）
用法：having 表达式

注意：
	1.having是用来对分组信息就行过滤，因此使用having时通常都会先实用group by；
	2.如果没使用gruop by，但使用了having，则意味着having把所有数据当作一组来过滤；
	3.having句中出现的字段必须是分组之后的组的整体信息，having句中不允许出现组内的详细信息；
	4.having和where同时用时，必须where写在having前面，顺序不可颠倒，因为where是对原始数据进行过滤，
		而having是对分组之后的数据进行过滤。
*/