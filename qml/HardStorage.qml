import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
Rectangle{
    id:storage;

    width:parent.width; height:parent.height; color:"#f0f0f0";
    anchors{left:parent.left;top:parent.top;}
    state:"hide";
    //border{color:"lime";width:10}

    ScrollView{
        id:scrollview_storage;

        anchors.fill:parent;
        Rectangle{
            id:emptylayer;

            width:parent.width; height:2000; color:"transparent";

            Text{
                id:title_chanpin;

                text:"产品";
                anchors{top:parent.top;topMargin:20;left:parent.left;leftMargin:15;}
            }
            Text{
                text:"三星 SSD 850 EVO 120GB（固态硬盘）";
                anchors{top:title_chanpin.top;left:parent.right;leftMargin:100;}
            }
            Text{
                id:title_rongliang;

                text:"容量";
                anchors{top:title_chanpin.bottom;topMargin:20;left:parent.left;leftMargin:15;}
            }
            Text{
                text:"120 GB";
                anchors{top:title_rongliang.top;left:parent.right;leftMargin:100;}
            }
            Text{
                id:title_xingzhuangtezheng;

                text:"形状特征";
                anchors{top:title_rongliang.bottom;topMargin:20;left:parent.left;leftMargin:15;}
            }
            Text{
                text:"2.5 寸";
                anchors{top:title_xingzhuangtezheng.top;left:parent.right;leftMargin:100;}
            }
            Text{
                id:title_cache;

                text:"缓存";
                anchors{top:title_xingzhuangtezheng.bottom;topMargin:20;left:parent.left;leftMargin:15;}
            }
            Text{
                text:"256 MB";
                anchors{top:title_cache.top;left:parent.right;leftMargin:100;}
            }
            Text{
                id:title_diskused;

                text:"硬盘已使用";
                anchors{top:title_cache.bottom;topMargin:20;left:parent.left;leftMargin:15;}
            }
            Text{
                text:"共9434次，累计8010小时";
                anchors{top:title_diskused.top;left:parent.right;leftMargin:100;}
            }
            Text{
                id:title_firm;

                text:"固件";
                anchors{top:title_diskused.bottom;topMargin:20;left:parent.left;leftMargin:15;}
            }
            Text{
                text:"EMT01B6Q";
                anchors{top:title_firm.top;left:parent.right;leftMargin:100;}
            }
            Text{
                id:title_jiekou;

                text:"接口";
                anchors{top:title_firm.bottom;topMargin:20;left:parent.left;leftMargin:15;}
            }
            Text{
                text:"SATA Ⅲ";
                anchors{top:title_jiekou.top;left:parent.right;leftMargin:100;}
            }
            Text{
                id:title_transferrate;

                text:"数据传输率";
                anchors{top:title_jiekou.bottom;topMargin:20;left:parent.left;leftMargin:15;}
            }
            Text{
                text:"600.00MB/秒";
                anchors{top:title_transferrate.top;left:parent.right;leftMargin:100;}
            }
            Text{
                id:title_charactor;

                text:"特征";
                anchors{top:title_transferrate.bottom;topMargin:20;left:parent.left;leftMargin:15;}
            }
            Text{
                text:"S.M.A.R.T 48-bit LBA NCQ";
                anchors{top:title_charactor.top;left:parent.right;leftMargin:100;}
            }
            Text{
                id:title_maincontroller;

                text:"主控制器";
                anchors{top:title_charactor.bottom;topMargin:20;left:parent.left;leftMargin:15;}
            }
            Text{
                text:"Samsung MGXS4LN062X01";
                anchors{top:title_maincontroller.top;left:parent.right;leftMargin:100;}
            }
            Text{
                id:title_flashtype;

                text:"闪存类型";
                anchors{top:title_maincontroller.bottom;topMargin:20;left:parent.left;leftMargin:15;}
            }
            Text{
                text:"Samsung 40nm TLC V-N";
                anchors{top:title_flashtype.top;left:parent.right;leftMargin:100;}
            }
            Text{
                id:title_sequentialread;

                text:"顺序读取速率";
                anchors{top:title_flashtype.bottom;topMargin:20;left:parent.left;leftMargin:15;}
            }
            Text{
                text:"540 MB/秒";
                anchors{top:title_sequentialread.top;left:parent.right;leftMargin:100;}
            }
            Text{
                id:title_sequentialwrite;

                text:"顺序写入速率";
                anchors{top:title_sequentialread.bottom;topMargin:20;left:parent.left;leftMargin:15;}
            }
            Text{
                text:"520 MB/秒";
                anchors{top:title_sequentialwrite.top;left:parent.right;leftMargin:100;}
            }
            Text{
                id:title_4kread;

                text:"4K随机读取";
                anchors{top:title_sequentialwrite.bottom;topMargin:20;left:parent.left;leftMargin:15;}
            }
            Text{
                text:"94 KIOPS";
                anchors{top:title_4kread.top;left:parent.right;leftMargin:100;}
            }
            Text{
                id:title_4kwrite;

                text:"4K随机写入";
                anchors{top:title_4kread.bottom;topMargin:20;left:parent.left;leftMargin:15;}
            }
            Text{
                text:"88 KIOPS";
                anchors{top:title_4kwrite.top;left:parent.right;leftMargin:100;}
            }
            Text{
                id:title_externalsize;

                text:"外形尺寸";
                anchors{top:title_4kwrite.bottom;topMargin:20;left:parent.left;leftMargin:15;}
            }
            Text{
                text:"69.85 x 100.00 x 6.80 毫米";
                anchors{top:title_externalsize.top;left:parent.right;leftMargin:100;}
            }
            Text{
                id:title_chosed;

                anchors{top:title_externalsize.bottom;topMargin:20;left:parent.left;leftMargin:40;}
                text:"选择";
            }
            ComboBox{
                id:combo_chosed_identify;

                currentIndex:1;
                model:ListModel{
                    //id:list_chosed;
                    ListElement{text:"disk 1";}
                    ListElement{text:"disk 2";}
                    ListElement{text:"disk 3";}
                }
                width:100;
                anchors{verticalCenter:title_chosed.verticalCenter;left:title_chosed.right;leftMargin:5;}

                style:ComboBoxStyle{
                    id:combo_style;

                    background: Rectangle{
                        id:combo_backgnd;

                        width:100; height:50; color:"white";

                        Rectangle{
                            id:outside_topline;

                            width:parent.width+2; height:1; color:"#a0a0a0";
                            anchors{top:parent.top;topMargin:-8;left:parent.left;}
                        }
                        Rectangle{
                            id:inside_topline;

                            width:parent.width; height:1; color:"#696969";
                            anchors{top:parent.top;topMargin:-7;left:parent.left;leftMargin:1;}
                        }
                        Rectangle{
                            id:outside_bottomline;

                            width:parent.width+2; height:1; color:"#ffffff";
                            anchors{top:parent.bottom;topMargin:7;left:parent.left;}
                        }
                        Rectangle{
                            id:inside_bottomline;

                            width:parent.width+1; height:1; color:"#e3e3e3";
                            anchors{top:parent.bottom;topMargin:6;left:parent.left;leftMargin:1;}
                        }
                        Rectangle{
                            id:outside_leftline;

                            width:1; height:parent.height+15; color:"#a0a0a0";
                            anchors{top:parent.top;topMargin:-7;left:parent.left;}
                        }
                        Rectangle{
                            id:inside_leftline;

                            width:1; height:parent.height+13; color:"#696969";
                            anchors{top:parent.top;topMargin:-6;left:parent.left;leftMargin:1;}
                        }
                        Rectangle{
                            id:outside_rightline;

                            width:1; height:parent.height+16; color:"#ffffff";
                            anchors{top:parent.top;topMargin:-8;left:parent.right;leftMargin:2;}
                        }
                        Rectangle{
                            id:inside_rightline;

                            width:1; height:parent.height+14; color:"#e3e3e3";
                            anchors{top:parent.top;topMargin:-7;left:parent.right;leftMargin:1;}
                        }
                        Rectangle{
                            id:btn

                            width:15; height:15; color:"#f0f0f0";
                            anchors{verticalCenter:parent.verticalCenter;right:parent.right;rightMargin:1;}
                            Rectangle{
                                id:btn_outside_topline;

                                width:parent.width+3; height:1; color:"#e3e3e3";
                                anchors{top:parent.top;topMargin:-2;left:parent.left;leftMargin:-2;}
                            }
                            Rectangle{
                                id:btn_inside_topline;

                                width:parent.width+1; height:1; color:"#ffffff";
                                anchors{top:parent.top;topMargin:-1;left:parent.left;leftMargin:-1;}
                            }
                            Rectangle{
                                id:btn_outside_bottomline;

                                width:parent.width+4; height:1; color:"#696969";
                                anchors{top:parent.bottom;topMargin:1;left:parent.left;leftMargin:-2;}
                            }
                            Rectangle{
                                id:btn_inside_bottomline;

                                width:parent.width+2; height:1; color:"#a0a0a0";
                                anchors{top:parent.bottom;left:parent.left;leftMargin:-1;}//anchors.topMargin:1;
                            }
                            Rectangle{
                                id:btn_outside_leftline;

                                width:1; height:parent.height+3; color:"#e3e3e3";
                                anchors{top:parent.top;topMargin:-2;left:parent.left;leftMargin:-2;}
                            }
                            Rectangle{
                                id:btn_inside_leftline;

                                width:1; height:parent.height+1; color:"#ffffff";
                                anchors{top:parent.top;topMargin:-1;left:parent.left;leftMargin:-1;}
                            }
                            Rectangle{
                                id:btn_outside_rightline;

                                width:1; height:parent.height+3; color:"#696969";
                                anchors{top:parent.top;topMargin:-2;left:parent.right;leftMargin:1;}
                            }
                            Rectangle{
                                id:btn_inside_rightline;

                                width:1; height:parent.height+1; color:"#a0a0a0";
                                anchors{top:parent.top;topMargin:-1;left:parent.right;}
                            }
                            //***************
                            Rectangle{
                                id:triangle7;

                                width:7; height:1; color:"#000000";
                                anchors{top:parent.top;topMargin:5;left:parent.left;leftMargin:3;}
                            }
                            Rectangle{
                                id:triangle5;

                                width:5; height:1; color:"#000000";
                                anchors{top:parent.top;topMargin:6;left:parent.left;leftMargin:4;}
                            }
                            Rectangle{
                                id:triangle3;

                                width:3; height:1; color:"#000000";
                                anchors{top:parent.top;topMargin:7;left:parent.left;leftMargin:5;}
                            }
                            Rectangle{
                                id:triangle1;

                                width:1; height:1; color:"#000000";
                                anchors{top:parent.top;topMargin:8;left:parent.left;leftMargin:6;}
                            }
                        }
                    }
                }
            }
            BasicTableView{
                id:identify_table;

                width:40*identify_table.columnCount; height:identify_table.rowCount*16+1;
                anchors{top:combo_chosed_identify.bottom;topMargin:20;left:parent.left;leftMargin:50;}

                model:ListModel{
                    ListElement{
                        col1:"0";
                        col2:"00";
                        col3:"01";
                        col4:"02";
                        col5:"03";
                        col6:"04";
                        col7:"05";
                        col8:"06";
                        col9:"07";
                        col10:"08";
                        col11:"09";
                        col12:"0A";
                        col13:"0B";
                        col14:"0C";
                        col15:"0D";
                        col16:"0E";
                        col17:"0F";
                    }
                    ListElement{
                        col1:"00";
                        col2:"00";
                        col3:"01";
                        col4:"02";
                        col5:"03";
                        col6:"04";
                        col7:"05";
                        col8:"06";
                        col9:"07";
                        col10:"08";
                        col11:"09";
                        col12:"0A";
                        col13:"0B";
                        col14:"0C";
                        col15:"0D";
                        col16:"0E";
                        col17:"0F";
                    }
                    ListElement{
                        col1:"01";
                        col2:"00";
                        col3:"01";
                        col4:"02";
                        col5:"03";
                        col6:"04";
                        col7:"05";
                        col8:"06";
                        col9:"07";
                        col10:"08";
                        col11:"09";
                        col12:"0A";
                        col13:"0B";
                        col14:"0C";
                        col15:"0D";
                        col16:"0E";
                        col17:"0F";
                    }
                    ListElement{
                        col1:"02";
                        col2:"00";
                        col3:"01";
                        col4:"02";
                        col5:"03";
                        col6:"04";
                        col7:"05";
                        col8:"06";
                        col9:"07";
                        col10:"08";
                        col11:"09";
                        col12:"0A";
                        col13:"0B";
                        col14:"0C";
                        col15:"0D";
                        col16:"0E";
                        col17:"0F";
                    }
                    ListElement{
                        col1:"03";
                        col2:"00";
                        col3:"01";
                        col4:"02";
                        col5:"03";
                        col6:"04";
                        col7:"05";
                        col8:"06";
                        col9:"07";
                        col10:"08";
                        col11:"09";
                        col12:"0A";
                        col13:"0B";
                        col14:"0C";
                        col15:"0D";
                        col16:"0E";
                        col17:"0F";
                    }
                    ListElement{
                        col1:"04";
                        col2:"00";
                        col3:"01";
                        col4:"02";
                        col5:"03";
                        col6:"04";
                        col7:"05";
                        col8:"06";
                        col9:"07";
                        col10:"08";
                        col11:"09";
                        col12:"0A";
                        col13:"0B";
                        col14:"0C";
                        col15:"0D";
                        col16:"0E";
                        col17:"0F";
                    }
                    ListElement{
                        col1:"05";
                        col2:"00";
                        col3:"01";
                        col4:"02";
                        col5:"03";
                        col6:"04";
                        col7:"05";
                        col8:"06";
                        col9:"07";
                        col10:"08";
                        col11:"09";
                        col12:"0A";
                        col13:"0B";
                        col14:"0C";
                        col15:"0D";
                        col16:"0E";
                        col17:"0F";
                    }
                    ListElement{
                        col1:"06";
                        col2:"00";
                        col3:"01";
                        col4:"02";
                        col5:"03";
                        col6:"04";
                        col7:"05";
                        col8:"06";
                        col9:"07";
                        col10:"08";
                        col11:"09";
                        col12:"0A";
                        col13:"0B";
                        col14:"0C";
                        col15:"0D";
                        col16:"0E";
                        col17:"0F";
                    }
                    ListElement{
                        col1:"07";
                        col2:"00";
                        col3:"01";
                        col4:"02";
                        col5:"03";
                        col6:"04";
                        col7:"05";
                        col8:"06";
                        col9:"07";
                        col10:"08";
                        col11:"09";
                        col12:"0A";
                        col13:"0B";
                        col14:"0C";
                        col15:"0D";
                        col16:"0E";
                        col17:"0F";
                    }
                    ListElement{
                        col1:"08";
                        col2:"00";
                        col3:"01";
                        col4:"02";
                        col5:"03";
                        col6:"04";
                        col7:"05";
                        col8:"06";
                        col9:"07";
                        col10:"08";
                        col11:"09";
                        col12:"0A";
                        col13:"0B";
                        col14:"0C";
                        col15:"0D";
                        col16:"0E";
                        col17:"0F";
                    }
                    ListElement{
                        col1:"09";
                        col2:"00";
                        col3:"01";
                        col4:"02";
                        col5:"03";
                        col6:"04";
                        col7:"05";
                        col8:"06";
                        col9:"07";
                        col10:"08";
                        col11:"09";
                        col12:"0A";
                        col13:"0B";
                        col14:"0C";
                        col15:"0D";
                        col16:"0E";
                        col17:"0F";
                    }
                    ListElement{
                        col1:"0A";
                        col2:"00";
                        col3:"01";
                        col4:"02";
                        col5:"03";
                        col6:"04";
                        col7:"05";
                        col8:"06";
                        col9:"07";
                        col10:"08";
                        col11:"09";
                        col12:"0A";
                        col13:"0B";
                        col14:"0C";
                        col15:"0D";
                        col16:"0E";
                        col17:"0F";
                    }
                    ListElement{
                        col1:"0B";
                        col2:"00";
                        col3:"01";
                        col4:"02";
                        col5:"03";
                        col6:"04";
                        col7:"05";
                        col8:"06";
                        col9:"07";
                        col10:"08";
                        col11:"09";
                        col12:"0A";
                        col13:"0B";
                        col14:"0C";
                        col15:"0D";
                        col16:"0E";
                        col17:"0F";
                    }
                    ListElement{
                        col1:"0C";
                        col2:"00";
                        col3:"01";
                        col4:"02";
                        col5:"03";
                        col6:"04";
                        col7:"05";
                        col8:"06";
                        col9:"07";
                        col10:"08";
                        col11:"09";
                        col12:"0A";
                        col13:"0B";
                        col14:"0C";
                        col15:"0D";
                        col16:"0E";
                        col17:"0F";
                    }
                    ListElement{
                        col1:"0D";
                        col2:"00";
                        col3:"01";
                        col4:"02";
                        col5:"03";
                        col6:"04";
                        col7:"05";
                        col8:"06";
                        col9:"07";
                        col10:"08";
                        col11:"09";
                        col12:"0A";
                        col13:"0B";
                        col14:"0C";
                        col15:"0D";
                        col16:"0E";
                        col17:"0F";
                    }
                    ListElement{
                        col1:"0E";
                        col2:"00";
                        col3:"01";
                        col4:"02";
                        col5:"03";
                        col6:"04";
                        col7:"05";
                        col8:"06";
                        col9:"07";
                        col10:"08";
                        col11:"09";
                        col12:"0A";
                        col13:"0B";
                        col14:"0C";
                        col15:"0D";
                        col16:"0E";
                        col17:"0F";
                    }
                    ListElement{
                        col1:"0F";
                        col2:"00";
                        col3:"01";
                        col4:"02";
                        col5:"03";
                        col6:"04";
                        col7:"05";
                        col8:"06";
                        col9:"07";
                        col10:"08";
                        col11:"09";
                        col12:"0A";
                        col13:"0B";
                        col14:"0C";
                        col15:"0D";
                        col16:"0E";
                        col17:"0F";
                    }
                }
                Component.onCompleted: identify_table.createTableViewColumn([["col1","col2","col3","col4","col5","col6","col7","col8","col9","col10","col11","col12","col13","col14","col15","col16","col17"],//
                                                                             ["Col1","Col2","Col3","Col4","Col5","Col6","Col7","Col8","Col9","Col10","Col11","Col12","Col13","Col14","Col15","Col16","Col17"],//
                                                                             [40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40]]);
            }
            ComboBox{
                id:combo_chosed_RW;

                currentIndex:1;
                model:ListModel{
                    //id:list_chosed;
                    ListElement{text:"disk 1";}
                    ListElement{text:"disk 2";}
                    ListElement{text:"disk 3";}
                }
                width:100;
                anchors{top:identify_table.bottom;topMargin:20;left:title_chosed.right;leftMargin:5;}
                style:ComboBoxStyle{
                    //id:combo_style;
                    background: Rectangle{
                        //id:combo_backgnd;
                        width:100; height:50; color:"white";

                        Rectangle{
                            //id:outside_topline;
                            width:parent.width+2; height:1; color:"#a0a0a0";
                            anchors{top:parent.top;topMargin:-8;left:parent.left;}
                        }
                        Rectangle{
                            //id:inside_topline;
                            width:parent.width; height:1; color:"#696969";
                            anchors{top:parent.top;topMargin:-7;left:parent.left;leftMargin:1;}
                        }
                        Rectangle{
                            //id:outside_bottomline;
                            width:parent.width+2; height:1; color:"#ffffff";
                            anchors{top:parent.bottom;topMargin:7;left:parent.left;}
                        }
                        Rectangle{
                            //id:inside_bottomline;
                            width:parent.width+1; height:1; color:"#e3e3e3";
                            anchors{top:parent.bottom;topMargin:6;left:parent.left;leftMargin:1;}
                        }
                        Rectangle{
                            //id:outside_leftline;
                            width:1; height:parent.height+15; color:"#a0a0a0";
                            anchors{top:parent.top;topMargin:-7;left:parent.left;}
                        }
                        Rectangle{
                            //id:inside_leftline;
                            width:1; height:parent.height+13; color:"#696969";
                            anchors{top:parent.top;topMargin:-6;left:parent.left;leftMargin:1;}
                        }
                        Rectangle{
                            //id:outside_rightline;
                            width:1; height:parent.height+16; color:"#ffffff";
                            anchors{top:parent.top;topMargin:-8;left:parent.right;leftMargin:2;}
                        }
                        Rectangle{
                            //id:inside_rightline;
                            width:1; height:parent.height+14; color:"#e3e3e3";
                            anchors{top:parent.top;topMargin:-7;left:parent.right;leftMargin:1;}
                        }
                        Rectangle{
                            //id:btn;
                            width:15; height:15; color:"#f0f0f0";
                            anchors{verticalCenter:parent.verticalCenter;right:parent.right;rightMargin:1;}
                            Rectangle{
                                //id:btn_outside_topline;
                                width:parent.width+3; height:1; color:"#e3e3e3";
                                anchors{top:parent.top;topMargin:-2;left:parent.left;leftMargin:-2;}
                            }
                            Rectangle{
                                //id:btn_inside_topline;
                                width:parent.width+1; height:1; color:"#ffffff";
                                anchors{top:parent.top;topMargin:-1;left:parent.left;leftMargin:-1;}
                            }
                            Rectangle{
                                //id:btn_outside_bottomline;
                                width:parent.width+4; height:1; color:"#696969";
                                anchors{top:parent.bottom;topMargin:1;left:parent.left;leftMargin:-2;}
                            }
                            Rectangle{
                                //id:btn_inside_bottomline;
                                width:parent.width+2; height:1; color:"#a0a0a0";
                                anchors{top:parent.bottom;left:parent.left;leftMargin:-1;}//anchors.topMargin:1;
                            }
                            Rectangle{
                               // id:btn_outside_leftline;
                                width:1; height:parent.height+3; color:"#e3e3e3";
                                anchors{top:parent.top;topMargin:-2;left:parent.left;leftMargin:-2;}
                            }
                            Rectangle{
                                //id:btn_inside_leftline;
                                width:1; height:parent.height+1; color:"#ffffff";
                                anchors{top:parent.top;topMargin:-1;left:parent.left;leftMargin:-1;}
                            }
                            Rectangle{
                                //id:btn_outside_rightline;
                                width:1; height:parent.height+3; color:"#696969";
                                anchors{top:parent.top;topMargin:-2;left:parent.right;leftMargin:1;}
                            }
                            Rectangle{
                                //id:btn_inside_rightline;
                                width:1; height:parent.height+1; color:"#a0a0a0";
                                anchors{top:parent.top;topMargin:-1;left:parent.right;}
                            }
                            //***************
                            Rectangle{
                                //id:triangle7;
                                width:7; height:1; color:"#000000";
                                anchors{top:parent.top;topMargin:5;left:parent.left;leftMargin:3;}
                            }
                            Rectangle{
                                //id:triangle5;
                                width:5; height:1; color:"#000000";
                                anchors{top:parent.top;topMargin:6;left:parent.left;leftMargin:4;}
                            }
                            Rectangle{
                                //id:triangle3;
                                width:3; height:1; color:"#000000";
                                anchors{top:parent.top;topMargin:7;left:parent.left;leftMargin:5;}
                            }
                            Rectangle{
                                //id:triangle1;
                                width:1; height:1; color:"#000000";
                                anchors{top:parent.top;topMargin:8;left:parent.left;leftMargin:6;}
                            }
                        }
                    }
                }
            }
            Text{
                id:title_LBA;

                text:"LBA";
                anchors{top:combo_chosed_RW.top;left:combo_chosed_RW.right;leftMargin:50;}
            }
            TextField{
                id:input_LBA;

                width:100; height:Text.contentHeight;
                anchors{top:title_LBA.top;topMargin:-7;left:title_LBA.right;leftMargin:5;}
            }

            BasicTableView{
                id:table_RW;

                width:40*table_RW.columnCount; height:table_RW.rowCount*16+1;
                anchors{top:combo_chosed_RW.bottom;topMargin:20;left:parent.left;leftMargin:50;}
                model:ListModel{
                    ListElement{
                        col1:"0";
                        col2:"00";
                        col3:"01";
                        col4:"02";
                        col5:"03";
                        col6:"04";
                        col7:"05";
                        col8:"06";
                        col9:"07";
                        col10:"08";
                        col11:"09";
                        col12:"0A";
                        col13:"0B";
                        col14:"0C";
                        col15:"0D";
                        col16:"0E";
                        col17:"0F";
                    }
                    ListElement{
                        col1:"00";
                        col2:"00";
                        col3:"01";
                        col4:"02";
                        col5:"03";
                        col6:"04";
                        col7:"05";
                        col8:"06";
                        col9:"07";
                        col10:"08";
                        col11:"09";
                        col12:"0A";
                        col13:"0B";
                        col14:"0C";
                        col15:"0D";
                        col16:"0E";
                        col17:"0F";
                    }
                    ListElement{
                        col1:"01";
                        col2:"00";
                        col3:"01";
                        col4:"02";
                        col5:"03";
                        col6:"04";
                        col7:"05";
                        col8:"06";
                        col9:"07";
                        col10:"08";
                        col11:"09";
                        col12:"0A";
                        col13:"0B";
                        col14:"0C";
                        col15:"0D";
                        col16:"0E";
                        col17:"0F";
                    }
                    ListElement{
                        col1:"02";
                        col2:"00";
                        col3:"01";
                        col4:"02";
                        col5:"03";
                        col6:"04";
                        col7:"05";
                        col8:"06";
                        col9:"07";
                        col10:"08";
                        col11:"09";
                        col12:"0A";
                        col13:"0B";
                        col14:"0C";
                        col15:"0D";
                        col16:"0E";
                        col17:"0F";
                    }
                    ListElement{
                        col1:"03";
                        col2:"00";
                        col3:"01";
                        col4:"02";
                        col5:"03";
                        col6:"04";
                        col7:"05";
                        col8:"06";
                        col9:"07";
                        col10:"08";
                        col11:"09";
                        col12:"0A";
                        col13:"0B";
                        col14:"0C";
                        col15:"0D";
                        col16:"0E";
                        col17:"0F";
                    }
                    ListElement{
                        col1:"04";
                        col2:"00";
                        col3:"01";
                        col4:"02";
                        col5:"03";
                        col6:"04";
                        col7:"05";
                        col8:"06";
                        col9:"07";
                        col10:"08";
                        col11:"09";
                        col12:"0A";
                        col13:"0B";
                        col14:"0C";
                        col15:"0D";
                        col16:"0E";
                        col17:"0F";
                    }
                    ListElement{
                        col1:"05";
                        col2:"00";
                        col3:"01";
                        col4:"02";
                        col5:"03";
                        col6:"04";
                        col7:"05";
                        col8:"06";
                        col9:"07";
                        col10:"08";
                        col11:"09";
                        col12:"0A";
                        col13:"0B";
                        col14:"0C";
                        col15:"0D";
                        col16:"0E";
                        col17:"0F";
                    }
                    ListElement{
                        col1:"06";
                        col2:"00";
                        col3:"01";
                        col4:"02";
                        col5:"03";
                        col6:"04";
                        col7:"05";
                        col8:"06";
                        col9:"07";
                        col10:"08";
                        col11:"09";
                        col12:"0A";
                        col13:"0B";
                        col14:"0C";
                        col15:"0D";
                        col16:"0E";
                        col17:"0F";
                    }
                    ListElement{
                        col1:"07";
                        col2:"00";
                        col3:"01";
                        col4:"02";
                        col5:"03";
                        col6:"04";
                        col7:"05";
                        col8:"06";
                        col9:"07";
                        col10:"08";
                        col11:"09";
                        col12:"0A";
                        col13:"0B";
                        col14:"0C";
                        col15:"0D";
                        col16:"0E";
                        col17:"0F";
                    }
                    ListElement{
                        col1:"08";
                        col2:"00";
                        col3:"01";
                        col4:"02";
                        col5:"03";
                        col6:"04";
                        col7:"05";
                        col8:"06";
                        col9:"07";
                        col10:"08";
                        col11:"09";
                        col12:"0A";
                        col13:"0B";
                        col14:"0C";
                        col15:"0D";
                        col16:"0E";
                        col17:"0F";
                    }
                    ListElement{
                        col1:"09";
                        col2:"00";
                        col3:"01";
                        col4:"02";
                        col5:"03";
                        col6:"04";
                        col7:"05";
                        col8:"06";
                        col9:"07";
                        col10:"08";
                        col11:"09";
                        col12:"0A";
                        col13:"0B";
                        col14:"0C";
                        col15:"0D";
                        col16:"0E";
                        col17:"0F";
                    }
                    ListElement{
                        col1:"0A";
                        col2:"00";
                        col3:"01";
                        col4:"02";
                        col5:"03";
                        col6:"04";
                        col7:"05";
                        col8:"06";
                        col9:"07";
                        col10:"08";
                        col11:"09";
                        col12:"0A";
                        col13:"0B";
                        col14:"0C";
                        col15:"0D";
                        col16:"0E";
                        col17:"0F";
                    }
                    ListElement{
                        col1:"0B";
                        col2:"00";
                        col3:"01";
                        col4:"02";
                        col5:"03";
                        col6:"04";
                        col7:"05";
                        col8:"06";
                        col9:"07";
                        col10:"08";
                        col11:"09";
                        col12:"0A";
                        col13:"0B";
                        col14:"0C";
                        col15:"0D";
                        col16:"0E";
                        col17:"0F";
                    }
                    ListElement{
                        col1:"0C";
                        col2:"00";
                        col3:"01";
                        col4:"02";
                        col5:"03";
                        col6:"04";
                        col7:"05";
                        col8:"06";
                        col9:"07";
                        col10:"08";
                        col11:"09";
                        col12:"0A";
                        col13:"0B";
                        col14:"0C";
                        col15:"0D";
                        col16:"0E";
                        col17:"0F";
                    }
                    ListElement{
                        col1:"0D";
                        col2:"00";
                        col3:"01";
                        col4:"02";
                        col5:"03";
                        col6:"04";
                        col7:"05";
                        col8:"06";
                        col9:"07";
                        col10:"08";
                        col11:"09";
                        col12:"0A";
                        col13:"0B";
                        col14:"0C";
                        col15:"0D";
                        col16:"0E";
                        col17:"0F";
                    }
                    ListElement{
                        col1:"0E";
                        col2:"00";
                        col3:"01";
                        col4:"02";
                        col5:"03";
                        col6:"04";
                        col7:"05";
                        col8:"06";
                        col9:"07";
                        col10:"08";
                        col11:"09";
                        col12:"0A";
                        col13:"0B";
                        col14:"0C";
                        col15:"0D";
                        col16:"0E";
                        col17:"0F";
                    }
                    ListElement{
                        col1:"0F";
                        col2:"00";
                        col3:"01";
                        col4:"02";
                        col5:"03";
                        col6:"04";
                        col7:"05";
                        col8:"06";
                        col9:"07";
                        col10:"08";
                        col11:"09";
                        col12:"0A";
                        col13:"0B";
                        col14:"0C";
                        col15:"0D";
                        col16:"0E";
                        col17:"0F";
                    }
                }
                Component.onCompleted: table_RW.createTableViewColumn([["col1","col2","col3","col4","col5","col6","col7","col8","col9","col10","col11","col12","col13","col14","col15","col16","col17"],//
                                                                             ["Col1","Col2","Col3","Col4","Col5","Col6","Col7","Col8","Col9","Col10","Col11","Col12","Col13","Col14","Col15","Col16","Col17"],//
                                                                             [40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40]]);

            }
            Rectangle{
                id:tree_usb;

                width:700; height:600;
                anchors{top:table_RW.bottom;topMargin:20;left:parent.left;leftMargin:50;}

                BasicTreeView{
                    anchors.fill:parent;
                    model:ListModel {
                        id: treemodel;

                        ListElement { text: "Level 1, Node 1" ;}
                        ListElement {
                            text: "Level 1, Node 2";
                            elements: [
                                ListElement { text: "Level 2, Node 1";
                                    elements: [
                                        ListElement { text: "Level 3, Node 1" ;}
                                    ]
                                },
                                ListElement { text: "Level 2, Node 2"; }
                            ]
                        }
                        ListElement { text: "Level 1, Node 3"; }
                    }
                }
            }
        }
    }

    Component.onCompleted: {
        //console.log("storage's state is",storage.state);
    }
    states:
    [
        State
        {
            name:"active";
            PropertyChanges
            {
                target: storage;
                //x:parent.x;
                //anchors.left:parent.left;
                visible:true;
            }

        },
        State
        {
            name:"hide";
            PropertyChanges
            {
                target: storage;
                //x:maincontent.x + 2*width;
                //anchors.left:parent.right;
                visible:false;
            }
        }

    ]

    transitions:Transition
    {
        PropertyAnimation
        {
            property:"visible";
            duration:100;
            easing.type: Easing.OutBounce;
            easing.amplitude: 0.1;
        }
    }
}
