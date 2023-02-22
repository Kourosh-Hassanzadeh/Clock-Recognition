#include <stdio.h>
#include <bmpio.h>
#include <math.h>

unsigned char picture[2000][2000][3];
unsigned char final[2000][2000][3];
int column1=0 ,row1=0 ,column2=-2 , row2=-2 , min_column=0 , max_column=0 ,min_row=0 ,max_row=0 ,row , column, number=1 ;
unsigned char pic[2000][2000][3];
unsigned char changed_pic[2000][2000][3];
unsigned char changed_pic1[2000][2000][3];
unsigned char average[2000][2000][3];
int sum[2000][2000][3];
int width , height;
double  newheight=860 , newwidth=850 , ratio1, ratio2 , ra1 , ra2;

void crop(void);
int find_column(void);
int find_row(void);
int find_min(void);
void transfer(void);
void horizontal_resize(void);
void vertical_resize(void);
void get_sum(void);
void get_average(void);
long long int subtract(void);
void black9(void);
void black0(void);
void black4(void);

int main(){	
	
	char address[100] , extra[100] , ex[100];
	int k, w=0 , min=0 , index , count=0,dif[10] , count1=0 , count2=0;
	printf("Please wait, it can takes a few minutes\n");
	/*for(w=0 ; w<=9 ; w++){

       for(k=1 ; k<=15 ; k++){
		
			sprintf(ex , "Dataset/%d/%d.bmp" ,w, k);
			readBMP(ex , &column,  &row , picture);
	
			int i,j,m=0,n=0 ,answer=0 , answer1=0;
	
			while(answer!=-1){
				crop();
		
				find_column();
				answer=find_min_row();
				find_row();
				if(answer!=-1){
		
					answer1=find_min_column();
					transfer();
		
					if(column1-column2>2 && row1-row2>2){
				
					ratio1= (newwidth)/(column1-column2);
			
					ra1=ratio1;
		
					ratio2=newheight/(row1-row2);
			
					ra2=ratio2;
			
					horizontal_resize();
					vertical_resize();
				
					}
					row2=-2;
					column2=-2;
				}
			}
			get_sum();
		}
		get_average();	
		sprintf(extra , "out%d.bmp", number );
		saveBMP(average , newwidth , newheight-10 , extra);
				
		number++;
		
	}*/
	
	printf("Please enter the address:\n");
	gets(address);
	printf("\n");
	readBMP(address , &column , &row , picture);
	int i,j,m=0,n=0 ,answer=0 , answer1=0, num=0;

	while(answer!=-1 && num!=6){
		crop();
	
		find_column();
		answer=find_min_row();
			
		find_row();
		if(answer!=-1){
	
			answer1=find_min_column();
			transfer();
		}
			
			
		if(column1-column2>2 && row1-row2>2){
		
			if(count1!=2 && count1!=3 && count1!=6 && count1!=7){
			
				ratio1= (newwidth)/(column1-column2);
		
				ra1=ratio1;
	
				ratio2=newheight/(row1-row2);
		
				ra2=ratio2;
		
				horizontal_resize();
				vertical_resize();
				
				for(i=1 ; i<=10 ; i++){
					
					sprintf(extra , "out%d.bmp", i);
					readBMP(extra , &width , &height , average);
					if(i==1){
						black0();
					}
					if(i==5){
						black4();	
					}
					/*if(i==9){
						black9();
					}*/
					if(i==10){
						black9();
						
					}
					dif[i-1]=subtract();
					
				}
				min=dif[0];
				for(i=0 ; i<=9 ; i++){
					
					if(dif[i]<=min){
						min=dif[i];
						index=i;
					}
					
				}
				count++;
				
				printf("%d", index);
				num++;
				if(count==2 || count==4){
					printf(":");
				}
				
			}
			count1++;
		}
		row2=-2;
		column2=-2;
	}
	
	printf("\n");	
	printf("\n");	
	printf("Thank you and good luck :) ");
	return 0;

}


void crop(void){
	int i,j,m,n,k=0,l=0;
	
	//saving the max and min of column
	for(i=0 ; i<column ; i++){
		for(j=0 ; j<row ; j++){
			if(!(picture[j][i][0]==255 && picture[j][i][1]==255 && picture[j][i][2]==255)){
		
				k++;
				if(k==1){ 
				
				min_column=i;
				}
				if (i > min_column){ 
				
				 max_column = i;
				}
			}
		}	
	
	}
	
	//saving the max and min of row
	for(m=0 ; m<row ; m++){
    	for(n=0 ; n<column ; n++){
	    	if(!(picture[m][n][0]==255 && picture[m][n][1]==255 && picture[m][n][2]==255)){
				l++;
				if(l==1){
					min_row=m;
				}
				if(m> min_row){
					max_row=m;
				
				}	
        	}
    	}	
	}	
}
int find_column(void){  //finding the max column that can be croped
		int i , j,k ,found=0;
		
		for(i=min_row ; i<=max_row ; i++){
			for(j=min_column ; j<=max_column ; j++){
				if((picture[i][j][0]==255 && picture[i][j][1]==255 && picture[i][j][2]==255)){
					 found=1;
					for(k=0 ; k<max_row ; k++){
						if(!(picture[k][j][0]==255 && picture[k][j][1]==255 && picture[k][j][2]==255)){
							
								found=0;
							}
					}
				
					if(found==1){
						column1=j;	
						
						return column1;	
					}
				}
			}
		}
		
		if(found==0){
			column1=max_column;
			return column1;
		}
		
		//return -1;
	}
	
	int find_min_row(void){  //find the min of row in range(mincoulmn--column1)
		int i,j,found=0;
		for(i=min_row ; i<max_row ; i++){
			
			for(j=min_column ; j<column1 ; j++){

				if(!(picture[i][j][0]==255 && picture[i][j][1]==255 && picture[i][j][2]==255)){
					found++;
					if(found==1){
						row2=i;
						
						return row2;
					}
				}
			}
		}
		if(row2==-2){
			
			return -1;
		}
		
		
	}

	int find_row(void){    //finding the max row that can be croped
		int i , j,k,found=0;
		
		
		for(j=min_column ; j<column1 ; j++){
		
			for(i=row2 ; i<max_row ; i++){
			
				if((picture[i][j][0]==255 && picture[i][j][1]==255 && picture[i][j][2]==255)){
					
					found=1;
					
					for(k=0 ; k<column1 ; k++){
						
						if(!(picture[i][k][0]==255 && picture[i][k][1]==255 && picture[i][k][2]==255)){
							
							found=0;
						}
					}
					if(found==1){
						
						row1=i;
		
						return row1;		
					}
				}
			}
		}
		if(found==0){
			row1=max_row;
			return row1;
		}
		
	//return -1;
	}

	int find_min_column(void){  //find the min of column in range(row2--row1)
		int i , j ,l,k, found=0, found1=0;
		
		for(l=min_column ; l<column1 ; l++){
			for(k=row2 ; k<row1 ; k++){
				if(!(picture[k][l][0]==255 && picture[k][l][1]==255 && picture[k][l][2]==255 )){
					found1++;
					if(found1==1){
						column2=l;
					
					}
				}
			}
		}
		if(column2==-2){
			return -1;
		}
		
		return 0;
	}
	void transfer(void){ //transfer that range from the original array to final array and delete previous shape
		int i , j , l=0 ,k=0;
		for(i=row2 ; i<=row1 ; i++){
			l=0;
			for(j=column2 ; j<=column1 ; j++){
				final[k][l][0]=picture[i][j][0];
				final[k][l][1]=picture[i][j][1];
				final[k][l][2]=picture[i][j][2];
				l++;
				picture[i][j][0]=255;
				picture[i][j][1]=255;
				picture[i][j][2]=255;
			}
			k++;
		}
		
	}


void horizontal_resize(void){  // resize the shape(digit) horizontally to a unique size
	int i , j , m=0 ,n;
	for(i=0 ; i<row1-row2 ; i++){
		m=0;
		for(j=0 ; j<newwidth ; j++){
		
			if(ra1>=1){
				changed_pic[i][j][0]=final[i][m][0];
				changed_pic[i][j][1]=final[i][m][1];
				changed_pic[i][j][2]=final[i][m][2];
				
				ra1-=1;
			}
			else{
				changed_pic[i][j][0]=(final[i][m][0]*ra1)+(final[i][m+1][0]*(1-ra1));
				changed_pic[i][j][1]=(final[i][m][1]*ra1)+(final[i][m+1][1]*(1-ra1));
				changed_pic[i][j][2]=(final[i][m][2]*ra1)+(final[i][m+1][2]*(1-ra1));
				
				ra1-=1;
			}
	
			if(ra1<0){
				ra1+=ratio1;	
				m++;
			}
		}
	}
}

void vertical_resize(void){  // resize the shape(digit) vertically to a unique size
	
	int i , j ,m ,n;
	
	for(j=0 ; j<newwidth ; j++){
		m=0;
		for(i=0 ; i<newheight ; i++){
			
			if(ra2>=1){
				changed_pic1[i][j][0]=changed_pic[m][j][0];
				changed_pic1[i][j][1]=changed_pic[m][j][1];
				changed_pic1[i][j][2]=changed_pic[m][j][2];
				
				ra2-=1;
			}
			else{
				changed_pic1[i][j][0]=(changed_pic[m][j][0]*ra2)+(changed_pic[m+1][j][0]*(1-ra2));
				changed_pic1[i][j][1]=(changed_pic[m][j][2]*ra2)+(changed_pic[m+1][j][1]*(1-ra2));
				changed_pic1[i][j][2]=(changed_pic[m][j][2]*ra2)+(changed_pic[m+1][j][2]*(1-ra2));
				
				ra2-=1;
			}
			if(ra2<0){
				ra2+=ratio2;
				m++;
			}
		}
	}
}

void get_sum(void){ //getting sum of data set 
	
	int i , j;
	for(i=0 ; i<newheight-10 ; i++){
		for(j=0 ; j<newwidth ; j++){
			
			sum[i][j][0]+=changed_pic1[i][j][0];
			sum[i][j][1]+=changed_pic1[i][j][1];
			sum[i][j][2]+=changed_pic1[i][j][2];
			
			
		}
	}
}	

void get_average(void){ //getting average of last function(sum)
	
	int i , j;
	for(i=0 ; i<newheight-10 ; i++){
		for(j=0 ; j<newwidth ; j++){
			average[i][j][0]=sum[i][j][0]/15;
			average[i][j][1]=sum[i][j][1]/15;
			average[i][j][2]=sum[i][j][2]/15;
			sum[i][j][0]=0;
			sum[i][j][1]=0;
			sum[i][j][2]=0;
			
		}
	}
	
}

long long int subtract(void){  //calculate the diference between average and clock that user puts
	
	int i , j ,subtract;
	for(i=0 ; i<newheight-10 ; i++){
		for(j=0 ; j<newwidth ; j++){
			subtract+=abs(changed_pic1[i][j][0]-average[i][j][0])+abs(changed_pic1[i][j][1]-average[i][j][1])+abs(changed_pic1[i][j][2]-average[i][j][2]);
			
		}
	}
	
	return subtract;
}

void black9(void){ // change the color intensity of number 9
	int i , j;
	for(i=0 ; i<newheight-10 ; i++){
		for(j=0 ; j<newwidth ; j++){
			if(average[i][j][0]<180 && average[i][j][1]<180 && average[i][j][2]<180){
				average[i][j][0]=0;
				average[i][j][1]=0;
				average[i][j][2]=0;
				
			}
			else{
				average[i][j][0]=255;
				average[i][j][1]=255;
				average[i][j][2]=255;
				
			}
		}
	}

}

void black0(void){  // change the color intensity of number 0

	int i , j;
	
	for(i=0 ; i<newheight-10 ; i++){
		for(j=0 ; j<newwidth ; j++){
			if(average[i][j][0]<100 && average[i][j][1]<100 && average[i][j][2]<100){
				average[i][j][0]=0;
				average[i][j][1]=0;
				average[i][j][2]=0;
				
			}
			else{
				average[i][j][0]=255;
				average[i][j][1]=255;
				average[i][j][2]=255;
				
			}
		}
	}
}
void black4(void){  // change the color intensity of number 4
	int i , j;
	
	for(i=0 ; i<newheight-10 ; i++){
		for(j=0 ; j<newwidth ; j++){
			if(average[i][j][0]<150 && average[i][j][1]<150 && average[i][j][2]<150){
				average[i][j][0]=0;
				average[i][j][1]=0;
				average[i][j][2]=0;
				
			}
			else{
				average[i][j][0]=255;
				average[i][j][1]=255;
				average[i][j][2]=255;
				
			}
		}
	}
}
