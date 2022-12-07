#include<stdio.h>
#include<conio.h>
#include<math.h>

inttochar(unsigned int);

main()
{
    unsigned char filename[100]={'0'},buffer[2]={'0'},temp;
    unsigned int  count=0;
    FILE *fp1,*fp2;

    printf("Enter name of any file:\n");
    scanf("%s",filename);

    fp1=fopen(filename,"rb");
    if(fp1==NULL)
    {
        printf("Input file cannot be opened...\n");
        return 0;
    }
    fp2=fopen("compressed.txt","wb");
    
    while(1)
    {
        if(!fread(buffer,1,1,fp1))
        {
            printf("EOF found....\n");
            break;
        }
        temp=buffer[0];
        if(!fread(buffer,1,1,fp1))
        {
            printf("EOF found....\n");
            break;
        }
        if(temp==buffer[0])
        {
            count=2;
            if(!fread(buffer,1,1,fp1))
            {
                printf("EOF found....\n");
                break;
            }
            while(temp==buffer[0])
            {
                count++;
                if(!fread(buffer,1,1,fp1))
                {
                    printf("EOF found....\n");
                    break;
                }
            }
            buffer[0]=temp;
            fwrite(buffer,1,1,fp2);
            buffer[0]=inttochar(count);
            fwrite(buffer,1,1,fp2);
            fseek(fp1,-1,SEEK_CUR);
        }
        else
        {
            fseek(fp1,-2,SEEK_CUR);
            if(!fread(buffer,1,1,fp1))
            {
                printf("EOF found....\n");
                break;
            }
            fwrite(buffer,1,1,fp2);
        }
    }
    printf("Closing the files...\n");
    fclose(fp1);
    fclose(fp2);
    return 0;
}

inttochar(unsigned int number)
{
    unsigned char chartoreturn='0';
    unsigned int sixteen=16,tempnumber=0;
    tempnumber=number;
    chartoreturn=number & 0x000f;
    number=tempnumber;
    number=number & 0x00f0;
    chartoreturn=chartoreturn | number;
   
    return (chartoreturn);
}