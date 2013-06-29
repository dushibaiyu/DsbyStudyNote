select reg_date from t_kenpin_data_2
select to_char(reg_date,'YYYY-MM-DD') AS REG_DATE from t_kenpin_data_2
--to_char：postgres自带函数，表示转换为文本信息，to_char（转换的列，转换格式）
