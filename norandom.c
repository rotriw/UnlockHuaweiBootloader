#include <stdlib.h>
#include <stdio.h>
int main(){
    unsigned char buffer_cmd[52]={112,108,97,116,102,111,114,109,45,116,111,111,108,115,92,102,97,115,116,98,111,111,116,32,111,101,109,32,117,110,108,111,99,107,32,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int buffer_get;
    fputs("order:",stderr);
    buffer_get=getche();
    fputs("\n\npuk0:",stderr);
    buffer_cmd[35]=getche();
    fputs("\npuk1:",stderr);
    buffer_cmd[36]=getche();
    fputs("\npuk2:",stderr);
    buffer_cmd[37]=getche();
    fputs("\npuk3:",stderr);
    buffer_cmd[38]=getche();
    fputs("\npuk4:",stderr);
    buffer_cmd[39]=getche();
    fputs("\npuk5:",stderr);
    buffer_cmd[40]=getche();
    fputs("\npuk6:",stderr);
    buffer_cmd[41]=getche();
    fputs("\npuk7:",stderr);
    buffer_cmd[42]=getche();
    fputs("\npuk8:",stderr);
    buffer_cmd[43]=getche();
    fputs("\npuk9:",stderr);
    buffer_cmd[44]=getche();
    fputs("\npuka:",stderr);
    buffer_cmd[45]=getche();
    fputs("\npukb:",stderr);
    buffer_cmd[46]=getche();
    fputs("\npukc:",stderr);
    buffer_cmd[47]=getche();
    fputs("\npukd:",stderr);
    buffer_cmd[48]=getche();
    fputs("\npuke:",stderr);
    buffer_cmd[49]=getche();
    fputs("\npukf:",stderr);
    buffer_cmd[50]=getche();
    fputs("\n\n",stderr);
    if(buffer_get==48){
        if(48<=buffer_cmd[35] && buffer_cmd[35]<=57 && 48<=buffer_cmd[36] && buffer_cmd[36]<=57 && 48<=buffer_cmd[37] && buffer_cmd[37]<=57 && 48<=buffer_cmd[38] && buffer_cmd[38]<=57 && 48<=buffer_cmd[39] && buffer_cmd[39]<=57 && 48<=buffer_cmd[40] && buffer_cmd[40]<=57 && 48<=buffer_cmd[41] && buffer_cmd[41]<=57 && 48<=buffer_cmd[42] && buffer_cmd[42]<=57 && 48<=buffer_cmd[43] && buffer_cmd[43]<=57 && 48<=buffer_cmd[44] && buffer_cmd[44]<=57 && 48<=buffer_cmd[45] && buffer_cmd[45]<=57 && 48<=buffer_cmd[46] && buffer_cmd[46]<=57 && 48<=buffer_cmd[47] && buffer_cmd[47]<=57 && 48<=buffer_cmd[48] && buffer_cmd[48]<=57 && 48<=buffer_cmd[49] && buffer_cmd[49]<=57 && 48<=buffer_cmd[50] && buffer_cmd[50]<=57){
            while(buffer_cmd[35]!=58){
                while(buffer_cmd[36]!=58){
                    while(buffer_cmd[37]!=58){
                        while(buffer_cmd[38]!=58){
                            while(buffer_cmd[39]!=58){
                                while(buffer_cmd[40]!=58){
                                    while(buffer_cmd[41]!=58){
                                        while(buffer_cmd[42]!=58){
                                            while(buffer_cmd[43]!=58){
                                                while(buffer_cmd[44]!=58){
                                                    while(buffer_cmd[45]!=58){
                                                        while(buffer_cmd[46]!=58){
                                                            while(buffer_cmd[47]!=58){
                                                                while(buffer_cmd[48]!=58){
                                                                    while(buffer_cmd[49]!=58){
                                                                        while(buffer_cmd[50]!=58){
                                                                            FILE *file_popen=_popen(buffer_cmd,"rb");
                                                                            while((buffer_get=getc(file_popen))!=EOF){
                                                                                if(buffer_get==79){
                                                                                    loop0:
                                                                                    if((buffer_get=getc(file_popen))==75){
                                                                                        if((buffer_get=getc(file_popen))==65){
                                                                                            if((buffer_get=getc(file_popen))==89){
                                                                                                buffer_cmd[26]=111;
                                                                                                buffer_cmd[27]=107;
                                                                                                buffer_cmd[28]=33;
                                                                                                buffer_cmd[29]=10;
                                                                                                buffer_cmd[30]=99;
                                                                                                buffer_cmd[31]=111;
                                                                                                buffer_cmd[32]=100;
                                                                                                buffer_cmd[33]=101;
                                                                                                buffer_cmd[34]=61;
                                                                                                fputs(buffer_cmd+26,stderr);
                                                                                                _pclose(file_popen);
                                                                                                system("pause");
                                                                                                return 0;
                                                                                            }
                                                                                            if(buffer_get==79){
                                                                                                goto loop0;
                                                                                            }
                                                                                        }
                                                                                        if(buffer_get==79){
                                                                                            goto loop0;
                                                                                        }
                                                                                    }
                                                                                    if(buffer_get==79){
                                                                                        goto loop0;
                                                                                    }
                                                                                }
                                                                            }
                                                                            _pclose(file_popen);
                                                                            buffer_cmd[50]++;
                                                                        }
                                                                        buffer_cmd[49]++;buffer_cmd[50]=48;
                                                                    }
                                                                    buffer_cmd[48]++;buffer_cmd[49]=48;buffer_cmd[50]=48;
                                                                }
                                                                buffer_cmd[47]++;buffer_cmd[48]=48;buffer_cmd[49]=48;buffer_cmd[50]=48;
                                                            }
                                                            buffer_cmd[46]++;buffer_cmd[47]=48;buffer_cmd[48]=48;buffer_cmd[49]=48;buffer_cmd[50]=48;
                                                        }
                                                        buffer_cmd[45]++;buffer_cmd[46]=48;buffer_cmd[47]=48;buffer_cmd[48]=48;buffer_cmd[49]=48;buffer_cmd[50]=48;
                                                    }
                                                    buffer_cmd[44]++;buffer_cmd[45]=48;buffer_cmd[46]=48;buffer_cmd[47]=48;buffer_cmd[48]=48;buffer_cmd[49]=48;buffer_cmd[50]=48;
                                                }
                                                buffer_cmd[43]++;buffer_cmd[44]=48;buffer_cmd[45]=48;buffer_cmd[46]=48;buffer_cmd[47]=48;buffer_cmd[48]=48;buffer_cmd[49]=48;buffer_cmd[50]=48;
                                            }
                                            buffer_cmd[42]++;buffer_cmd[43]=48;buffer_cmd[44]=48;buffer_cmd[45]=48;buffer_cmd[46]=48;buffer_cmd[47]=48;buffer_cmd[48]=48;buffer_cmd[49]=48;buffer_cmd[50]=48;
                                        }
                                        buffer_cmd[41]++;buffer_cmd[42]=48;buffer_cmd[43]=48;buffer_cmd[44]=48;buffer_cmd[45]=48;buffer_cmd[46]=48;buffer_cmd[47]=48;buffer_cmd[48]=48;buffer_cmd[49]=48;buffer_cmd[50]=48;
                                    }
                                    buffer_cmd[40]++;buffer_cmd[41]=48;buffer_cmd[42]=48;buffer_cmd[43]=48;buffer_cmd[44]=48;buffer_cmd[45]=48;buffer_cmd[46]=48;buffer_cmd[47]=48;buffer_cmd[48]=48;buffer_cmd[49]=48;buffer_cmd[50]=48;
                                }
                                buffer_cmd[39]++;buffer_cmd[40]=48;buffer_cmd[41]=48;buffer_cmd[42]=48;buffer_cmd[43]=48;buffer_cmd[44]=48;buffer_cmd[45]=48;buffer_cmd[46]=48;buffer_cmd[47]=48;buffer_cmd[48]=48;buffer_cmd[49]=48;buffer_cmd[50]=48;
                            }
                            buffer_cmd[38]++;buffer_cmd[39]=48;buffer_cmd[40]=48;buffer_cmd[41]=48;buffer_cmd[42]=48;buffer_cmd[43]=48;buffer_cmd[44]=48;buffer_cmd[45]=48;buffer_cmd[46]=48;buffer_cmd[47]=48;buffer_cmd[48]=48;buffer_cmd[49]=48;buffer_cmd[50]=48;
                        }
                        buffer_cmd[37]++;buffer_cmd[38]=48;buffer_cmd[39]=48;buffer_cmd[40]=48;buffer_cmd[41]=48;buffer_cmd[42]=48;buffer_cmd[43]=48;buffer_cmd[44]=48;buffer_cmd[45]=48;buffer_cmd[46]=48;buffer_cmd[47]=48;buffer_cmd[48]=48;buffer_cmd[49]=48;buffer_cmd[50]=48;
                    }
                    buffer_cmd[36]++;buffer_cmd[37]=48;buffer_cmd[38]=48;buffer_cmd[39]=48;buffer_cmd[40]=48;buffer_cmd[41]=48;buffer_cmd[42]=48;buffer_cmd[43]=48;buffer_cmd[44]=48;buffer_cmd[45]=48;buffer_cmd[46]=48;buffer_cmd[47]=48;buffer_cmd[48]=48;buffer_cmd[49]=48;buffer_cmd[50]=48;
                }
                buffer_cmd[35]++;buffer_cmd[36]=48;buffer_cmd[37]=48;buffer_cmd[38]=48;buffer_cmd[39]=48;buffer_cmd[40]=48;buffer_cmd[41]=48;buffer_cmd[42]=48;buffer_cmd[43]=48;buffer_cmd[44]=48;buffer_cmd[45]=48;buffer_cmd[46]=48;buffer_cmd[47]=48;buffer_cmd[48]=48;buffer_cmd[49]=48;buffer_cmd[50]=48;
            }
        }else{
            fputs("puk ",stderr);
            if(!(buffer_cmd[35]<=57 && buffer_cmd[35]>=48)){fputs("0,",stderr);}
            if(!(buffer_cmd[36]<=57 && buffer_cmd[35]>=48)){fputs("1,",stderr);}
            if(!(buffer_cmd[37]<=57 && buffer_cmd[35]>=48)){fputs("2,",stderr);}
            if(!(buffer_cmd[38]<=57 && buffer_cmd[35]>=48)){fputs("3,",stderr);}
            if(!(buffer_cmd[39]<=57 && buffer_cmd[35]>=48)){fputs("4,",stderr);}
            if(!(buffer_cmd[40]<=57 && buffer_cmd[35]>=48)){fputs("5,",stderr);}
            if(!(buffer_cmd[41]<=57 && buffer_cmd[35]>=48)){fputs("6,",stderr);}
            if(!(buffer_cmd[42]<=57 && buffer_cmd[35]>=48)){fputs("7,",stderr);}
            if(!(buffer_cmd[43]<=57 && buffer_cmd[35]>=48)){fputs("8,",stderr);}
            if(!(buffer_cmd[44]<=57 && buffer_cmd[35]>=48)){fputs("9,",stderr);}
            if(!(buffer_cmd[45]<=57 && buffer_cmd[35]>=48)){fputs("a,",stderr);}
            if(!(buffer_cmd[46]<=57 && buffer_cmd[35]>=48)){fputs("b,",stderr);}
            if(!(buffer_cmd[47]<=57 && buffer_cmd[35]>=48)){fputs("c,",stderr);}
            if(!(buffer_cmd[48]<=57 && buffer_cmd[35]>=48)){fputs("d,",stderr);}
            if(!(buffer_cmd[49]<=57 && buffer_cmd[35]>=48)){fputs("e,",stderr);}
            if(!(buffer_cmd[50]<=57 && buffer_cmd[35]>=48)){fputs("f,",stderr);}
            fputs(" error\n",stderr);
            system("pause");
            return 0;
        }
    }else if(buffer_get==49){
        if(48<=buffer_cmd[35] && buffer_cmd[35]<=57 && 48<=buffer_cmd[36] && buffer_cmd[36]<=57 && 48<=buffer_cmd[37] && buffer_cmd[37]<=57 && 48<=buffer_cmd[38] && buffer_cmd[38]<=57 && 48<=buffer_cmd[39] && buffer_cmd[39]<=57 && 48<=buffer_cmd[40] && buffer_cmd[40]<=57 && 48<=buffer_cmd[41] && buffer_cmd[41]<=57 && 48<=buffer_cmd[42] && buffer_cmd[42]<=57 && 48<=buffer_cmd[43] && buffer_cmd[43]<=57 && 48<=buffer_cmd[44] && buffer_cmd[44]<=57 && 48<=buffer_cmd[45] && buffer_cmd[45]<=57 && 48<=buffer_cmd[46] && buffer_cmd[46]<=57 && 48<=buffer_cmd[47] && buffer_cmd[47]<=57 && 48<=buffer_cmd[48] && buffer_cmd[48]<=57 && 48<=buffer_cmd[49] && buffer_cmd[49]<=57 && 48<=buffer_cmd[50] && buffer_cmd[50]<=57){
            while(buffer_cmd[35]!=47){
                while(buffer_cmd[36]!=47){
                    while(buffer_cmd[37]!=47){
                        while(buffer_cmd[38]!=47){
                            while(buffer_cmd[39]!=47){
                                while(buffer_cmd[40]!=47){
                                    while(buffer_cmd[41]!=47){
                                        while(buffer_cmd[42]!=47){
                                            while(buffer_cmd[43]!=47){
                                                while(buffer_cmd[44]!=47){
                                                    while(buffer_cmd[45]!=47){
                                                        while(buffer_cmd[46]!=47){
                                                            while(buffer_cmd[47]!=47){
                                                                while(buffer_cmd[48]!=47){
                                                                    while(buffer_cmd[49]!=47){
                                                                        while(buffer_cmd[50]!=47){
                                                                            FILE *file_popen=_popen(buffer_cmd,"rb");
                                                                            while((buffer_get=getc(file_popen))!=EOF){
                                                                                if(buffer_get==79){
                                                                                    loop1:
                                                                                    if((buffer_get=getc(file_popen))==75){
                                                                                        if((buffer_get=getc(file_popen))==65){
                                                                                            if((buffer_get=getc(file_popen))==89){
                                                                                                buffer_cmd[26]=111;
                                                                                                buffer_cmd[27]=107;
                                                                                                buffer_cmd[28]=33;
                                                                                                buffer_cmd[29]=10;
                                                                                                buffer_cmd[30]=99;
                                                                                                buffer_cmd[31]=111;
                                                                                                buffer_cmd[32]=100;
                                                                                                buffer_cmd[33]=101;
                                                                                                buffer_cmd[34]=61;
                                                                                                fputs(buffer_cmd+26,stderr);
                                                                                                _pclose(file_popen);
                                                                                                system("pause");
                                                                                                return 0;
                                                                                            }
                                                                                            if(buffer_get==79){
                                                                                                goto loop1;
                                                                                            }
                                                                                        }
                                                                                        if(buffer_get==79){
                                                                                            goto loop1;
                                                                                        }
                                                                                    }
                                                                                    if(buffer_get==79){
                                                                                        goto loop1;
                                                                                    }
                                                                                }
                                                                            }
                                                                            _pclose(file_popen);
                                                                            buffer_cmd[50]--;
                                                                        }
                                                                        buffer_cmd[49]--;buffer_cmd[50]=57;
                                                                    }
                                                                    buffer_cmd[48]--;buffer_cmd[49]=57;buffer_cmd[50]=57;
                                                                }
                                                                buffer_cmd[47]--;buffer_cmd[48]=57;buffer_cmd[49]=57;buffer_cmd[50]=57;
                                                            }
                                                            buffer_cmd[46]--;buffer_cmd[47]=57;buffer_cmd[48]=57;buffer_cmd[49]=57;buffer_cmd[50]=57;
                                                        }
                                                        buffer_cmd[45]--;buffer_cmd[46]=57;buffer_cmd[47]=57;buffer_cmd[48]=57;buffer_cmd[49]=57;buffer_cmd[50]=57;
                                                    }
                                                    buffer_cmd[44]--;buffer_cmd[45]=57;buffer_cmd[46]=57;buffer_cmd[47]=57;buffer_cmd[48]=57;buffer_cmd[49]=57;buffer_cmd[50]=57;
                                                }
                                                buffer_cmd[43]--;buffer_cmd[44]=57;buffer_cmd[45]=57;buffer_cmd[46]=57;buffer_cmd[47]=57;buffer_cmd[48]=57;buffer_cmd[49]=57;buffer_cmd[50]=57;
                                            }
                                            buffer_cmd[42]--;buffer_cmd[43]=57;buffer_cmd[44]=57;buffer_cmd[45]=57;buffer_cmd[46]=57;buffer_cmd[47]=57;buffer_cmd[48]=57;buffer_cmd[49]=57;buffer_cmd[50]=57;
                                        }
                                        buffer_cmd[41]--;buffer_cmd[42]=57;buffer_cmd[43]=57;buffer_cmd[44]=57;buffer_cmd[45]=57;buffer_cmd[46]=57;buffer_cmd[47]=57;buffer_cmd[48]=57;buffer_cmd[49]=57;buffer_cmd[50]=57;
                                    }
                                    buffer_cmd[40]--;buffer_cmd[41]=57;buffer_cmd[42]=57;buffer_cmd[43]=57;buffer_cmd[44]=57;buffer_cmd[45]=57;buffer_cmd[46]=57;buffer_cmd[47]=57;buffer_cmd[48]=57;buffer_cmd[49]=57;buffer_cmd[50]=57;
                                }
                                buffer_cmd[39]--;buffer_cmd[40]=57;buffer_cmd[41]=57;buffer_cmd[42]=57;buffer_cmd[43]=57;buffer_cmd[44]=57;buffer_cmd[45]=57;buffer_cmd[46]=57;buffer_cmd[47]=57;buffer_cmd[48]=57;buffer_cmd[49]=57;buffer_cmd[50]=57;
                            }
                            buffer_cmd[38]--;buffer_cmd[39]=57;buffer_cmd[40]=57;buffer_cmd[41]=57;buffer_cmd[42]=57;buffer_cmd[43]=57;buffer_cmd[44]=57;buffer_cmd[45]=57;buffer_cmd[46]=57;buffer_cmd[47]=57;buffer_cmd[48]=57;buffer_cmd[49]=57;buffer_cmd[50]=57;
                        }
                        buffer_cmd[37]--;buffer_cmd[38]=57;buffer_cmd[39]=57;buffer_cmd[40]=57;buffer_cmd[41]=57;buffer_cmd[42]=57;buffer_cmd[43]=57;buffer_cmd[44]=57;buffer_cmd[45]=57;buffer_cmd[46]=57;buffer_cmd[47]=57;buffer_cmd[48]=57;buffer_cmd[49]=57;buffer_cmd[50]=57;
                    }
                    buffer_cmd[36]--;buffer_cmd[37]=57;buffer_cmd[38]=57;buffer_cmd[39]=57;buffer_cmd[40]=57;buffer_cmd[41]=57;buffer_cmd[42]=57;buffer_cmd[43]=57;buffer_cmd[44]=57;buffer_cmd[45]=57;buffer_cmd[46]=57;buffer_cmd[47]=57;buffer_cmd[48]=57;buffer_cmd[49]=57;buffer_cmd[50]=57;
                }
                buffer_cmd[35]--;buffer_cmd[36]=57;buffer_cmd[37]=57;buffer_cmd[38]=57;buffer_cmd[39]=57;buffer_cmd[40]=57;buffer_cmd[41]=57;buffer_cmd[42]=57;buffer_cmd[43]=57;buffer_cmd[44]=57;buffer_cmd[45]=57;buffer_cmd[46]=57;buffer_cmd[47]=57;buffer_cmd[48]=57;buffer_cmd[49]=57;buffer_cmd[50]=57;
            }
        }else{
            fputs("puk ",stderr);
            if(!(buffer_cmd[35]<=57 && buffer_cmd[35]>=48)){fputs("0,",stderr);}
            if(!(buffer_cmd[36]<=57 && buffer_cmd[35]>=48)){fputs("1,",stderr);}
            if(!(buffer_cmd[37]<=57 && buffer_cmd[35]>=48)){fputs("2,",stderr);}
            if(!(buffer_cmd[38]<=57 && buffer_cmd[35]>=48)){fputs("3,",stderr);}
            if(!(buffer_cmd[39]<=57 && buffer_cmd[35]>=48)){fputs("4,",stderr);}
            if(!(buffer_cmd[40]<=57 && buffer_cmd[35]>=48)){fputs("5,",stderr);}
            if(!(buffer_cmd[41]<=57 && buffer_cmd[35]>=48)){fputs("6,",stderr);}
            if(!(buffer_cmd[42]<=57 && buffer_cmd[35]>=48)){fputs("7,",stderr);}
            if(!(buffer_cmd[43]<=57 && buffer_cmd[35]>=48)){fputs("8,",stderr);}
            if(!(buffer_cmd[44]<=57 && buffer_cmd[35]>=48)){fputs("9,",stderr);}
            if(!(buffer_cmd[45]<=57 && buffer_cmd[35]>=48)){fputs("a,",stderr);}
            if(!(buffer_cmd[46]<=57 && buffer_cmd[35]>=48)){fputs("b,",stderr);}
            if(!(buffer_cmd[47]<=57 && buffer_cmd[35]>=48)){fputs("c,",stderr);}
            if(!(buffer_cmd[48]<=57 && buffer_cmd[35]>=48)){fputs("d,",stderr);}
            if(!(buffer_cmd[49]<=57 && buffer_cmd[35]>=48)){fputs("e,",stderr);}
            if(!(buffer_cmd[50]<=57 && buffer_cmd[35]>=48)){fputs("f,",stderr);}
            fputs(" error\n",stderr);
            system("pause");
            return 0;
        }
    }else{
        fputs("order error\n",stderr);
        system("pause");
        return 0;
    }
    system("pause");
    return 0;
}