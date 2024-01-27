SET FOREIGN_KEY_CHECKS=0;

DROP TABLE IF EXISTS `user`;
CREATE TABLE `user` (
  `id` int(11) NOT NULL DEFAULT '0',
  `username` text,
  `password` text,
  `is_admin` BOOLEAN,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


INSERT INTO `user` VALUES ('1', 'admin', 'admin', 1);
INSERT INTO `user` VALUES ('2', 'rick', '123456', 0);
INSERT INTO `user` VALUES ('3', 'jay', '123456', 0);

DROP TABLE IF EXISTS `clerk`;
CREATE TABLE `clerk` (
  `id` int(11) NOT NULL COMMENT 'id',
  `name` varchar(20) DEFAULT NULL COMMENT '职员姓名',
  `sex` char(1) DEFAULT NULL COMMENT '性别:0->女,1->男',
  `phone_number` char(11) DEFAULT NULL COMMENT '手机号码',
  `id_card` char(18) DEFAULT NULL COMMENT '身份证号',
  `address` varchar(50) DEFAULT NULL COMMENT '家庭住址',
  `position` varchar(25) DEFAULT NULL COMMENT '职位',
  `department_id` int(11) DEFAULT NULL COMMENT '部门编号',
  `user_id` int(11) DEFAULT NULL COMMENT '用户账号编号',
  `hire_date` date DEFAULT NULL COMMENT '入职时间',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='职员表';

INSERT INTO `clerk` (`id`, `name`, `sex`, `phone_number`, `id_card`, `address`, `position`, `department_id`, `user_id`, `hire_date`) VALUES (1, '董悦', '0', '13470085017', '142601199902147611', '翻斗花园', '经理', '1', 2, '2024-01-23');

INSERT INTO `clerk` (`id`, `name`, `sex`, `phone_number`, `id_card`, `address`, `position`, `department_id`, `user_id`, `hire_date`) VALUES (2, '董余辉', '1', '13470085008', '142601199308147655', '翻斗花园', '职工', '1', 2, '2024-01-23');


CREATE TABLE `department` (
  `id` int(11) NOT NULL COMMENT 'id',
  `name` varchar(20) DEFAULT NULL COMMENT '部门名称',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8  COMMENT='部门表';

INSERT INTO `department` (`id`, `name`) VALUES (1, '研发部');
INSERT INTO `department` (`id`, `name`) VALUES (2, '人事部');
INSERT INTO `department` (`id`, `name`) VALUES (3, '市场部');




