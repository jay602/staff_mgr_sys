SET FOREIGN_KEY_CHECKS=0;

DROP TABLE IF EXISTS `user`;
CREATE TABLE `user` (
  `id` int AUTO_INCREMENT,
  `username` text,
  `password` text,
  `is_admin` BOOLEAN,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

INSERT INTO `user` (`username`, `password`, `is_admin`) VALUES ('admin', 'admin', 1);
INSERT INTO `user` (`username`, `password`, `is_admin`) VALUES ('rick', '123456', 0);
INSERT INTO `user`(`username`, `password`, `is_admin`)  VALUES ('jay', '123456', 0);


DROP TABLE IF EXISTS `clerk`;
CREATE TABLE `clerk` (
   `id` int AUTO_INCREMENT COMMENT 'id',
  `name` varchar(20) DEFAULT NULL COMMENT '职员姓名',
  `sex` char(1) DEFAULT NULL COMMENT '性别:0->女,1->男',
  `phone_number` char(11) DEFAULT NULL COMMENT '手机号码',
  `id_card` char(18) DEFAULT NULL COMMENT '身份证号',
  `address` varchar(50) DEFAULT NULL COMMENT '家庭住址',
  `position` varchar(25) DEFAULT NULL COMMENT '职位',
  `department_id` int(11) DEFAULT NULL COMMENT '部门编号',
  `user_id` int DEFAULT NULL COMMENT '用户账号编号',
  `hire_date` date DEFAULT NULL COMMENT '入职时间',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='职员表';

INSERT INTO `clerk` (`name`, `sex`, `phone_number`, `id_card`, `address`, `position`, `department_id`, `user_id`, `hire_date`) VALUES ('董悦', '0', '13470085017', '142601199902147611', '翻斗花园', '经理', '1', 2, '2020-01-2');

INSERT INTO `clerk` (`name`, `sex`, `phone_number`, `id_card`, `address`, `position`, `department_id`, `user_id`, `hire_date`) VALUES ('董余辉', '1', '13470085008', '142601199308147655', '翻斗花园', '职工', '1', 1, '2022-01-23');



DROP TABLE IF EXISTS `department`;
CREATE TABLE `department` (
   `id` int AUTO_INCREMENT COMMENT 'id',
  `name` varchar(20) DEFAULT NULL COMMENT '部门名称',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8  COMMENT='部门表';

INSERT INTO `department` (`name`) VALUES ('研发部');
INSERT INTO `department` (`name`) VALUES ('人事部');
INSERT INTO `department` (`name`) VALUES ('市场部');


DROP TABLE IF EXISTS `attendance`;

CREATE TABLE `attendance` (
  `id` int AUTO_INCREMENT COMMENT 'id',
  `status` char(1) DEFAULT '0' COMMENT '正常0,事假1,迟到2,早退3,病假4,旷工5',
  `attendance_date` date DEFAULT NULL COMMENT '时间',
  `clerk_id` int DEFAULT NULL COMMENT '员工id',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='考勤表';

INSERT INTO `attendance` (`status`, `attendance_date`, `clerk_id`) VALUES ('1', '2022-03-23', 2);
INSERT INTO `attendance` (`status`, `attendance_date`, `clerk_id`) VALUES ('1', '2022-03-25', 2);


DROP TABLE IF EXISTS `attendance_name`;
CREATE TABLE `attendance_name` (
   `id` int AUTO_INCREMENT COMMENT 'id',
  `name` varchar(20) DEFAULT NULL COMMENT '考勤名称',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8  COMMENT='考勤名称';

INSERT INTO `attendance_name` (`name`) VALUES ('正常');
INSERT INTO `attendance_name` (`name`) VALUES ('事假');
INSERT INTO `attendance_name` (`name`) VALUES ('迟到');
INSERT INTO `attendance_name` (`name`) VALUES ('早退');
INSERT INTO `attendance_name` (`name`) VALUES ('病假');
INSERT INTO `attendance_name` (`name`) VALUES ('旷工');


DROP TABLE IF EXISTS `salary`;

CREATE TABLE `salary` (
  `clerk_id` int NOT NULL COMMENT '员工编号',
  `year` INT check(year BETWEEN 2015 AND 2099),     
  `month` INT CHECK(month BETWEEN 1 AND 12),      
  basic_pay INT COMMENT '基本工资', 
  butie_pay INT COMMENT '补贴工资', 
  kouchu_pay INT COMMENT '扣除工资',   
  yingfa_pay INT COMMENT '应发工资',  
  shifa_pay INT COMMENT '实发工资', 
  PRIMARY KEY (clerk_id, year, month)
)ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='工资表';













