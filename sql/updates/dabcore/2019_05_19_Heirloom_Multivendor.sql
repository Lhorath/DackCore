SET @MENU_ID = (SELECT max(menuid)+1 FROM gossip_menu_option);


INSERT INTO `gossip_menu_option` (`menuid`, `optionid`, `optionicon`, `optiontext`, `optiontype`, `optionnpcflag`, `actionmenuid`, `actionpoiid`, `boxcoded`, `boxmoney`, `boxtext`) VALUES
(@MENU_ID, 0, 4, 'Cloth Armor', 3, 128, 191000, 0, 0, 0, 'Cloth Heirlooms'),
(@MENU_ID, 1, 4, 'Leather Armor', 3, 128, 191001, 0, 0, 0, 'Leather Heirlooms'),
(@MENU_ID, 2, 4, 'Mail Armor', 3, 128, 191002, 0, 0, 0,'Mail Heirlooms'),
(@MENU_ID, 3, 4, 'Plate Armor', 3, 128, 191003, 0, 0, 0, 'Plate Heirlooms'),
(@MENU_ID, 4, 4, 'Weapons & Offhand', 3, 128, 191004, 0, 0, 0, 'Heirloom Weapons and Off-Hands'),
(@MENU_ID, 5, 4, 'Accessories', 3, 128, 191005, 0, 0, 0, 'Heirloom Accessories');