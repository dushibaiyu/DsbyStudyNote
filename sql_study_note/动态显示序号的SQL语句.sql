select
(select count(*) from m_opt a where a.opt_id <= b.opt_id) as no
,opt_id, opt_name 
from m_opt b
group by opt_id
order by opt_id