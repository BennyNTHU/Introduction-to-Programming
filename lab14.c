/*EE231002 Lab 16 Image Processing
  103061232.Chong-yao,Zhang Jian
  Date:2015.1.1
*/

#include <stdio.h>
#include <stdlib.h>
#define width 0
#define height 1

typedef struct sPIXEL{		//a single pixel
	unsigned char r,g,b;	//three color components
} PIXEL;

typedef struct sIMG{		//an imageof PPM format
	char header[3];			//header,either P3 or P6
	int W,H;				//width and height
	int level;				//intensity level of each color
	PIXEL **PX;				//2D array for all the pixels
} IMG;

IMG *PPMin(char *inFile);               //read image
void *PPMout(IMG *p1,char *outFile);    //print image
IMG *PPMcvt(IMG *p1,IMG *ee,IMG *nthu); //compose image

int main(int argc,char *argv[]){
	IMG *back,*ee,*nthu;	//declare pointer points to image

	back=PPMin(argv[1]);	//read background photo
	ee=PPMin(argv[2]);		//read EE logo
	nthu=PPMin(argv[3]);	//read NTHU logo
	PPMcvt(back,ee,nthu);	//compose image
	PPMout(back,argv[4]);	//print image

	return 0;				//program end
}

IMG *PPMin(char *inFile){
	int i,j;								 //looping index
	FILE *file;
	IMG *image=(IMG*)malloc(sizeof(IMG));

	file=fopen(inFile,"r");					 //open file
	fscanf(file,"%s",image->header);		 //scan P6
	fscanf(file,"%d %d\n%d\n",&image->W,&image->H,&image->level);//scan info
	image->PX=(PIXEL**)malloc(image->W * sizeof(PIXEL*));
	for(i=0;i<image->W;i++){
		image->PX[i]=(PIXEL*)malloc(image->H * sizeof(PIXEL));
	}
	for(i=0;i<image->H;i++){
		for(j=0;j<image->W;j++){
			image->PX[j][i].r=fgetc(file);	 //get pixel
			image->PX[j][i].g=fgetc(file);	 //...
			image->PX[j][i].b=fgetc(file);	 //...
		}
	}
	fclose(file);							 //close file

	return image;							 //return pointer
}

void *PPMout(IMG *p1,char *outFile){
	FILE *out;
	int i,j;

    out=fopen(outFile,"w");              //open output file
    fprintf(out,"%s\n",p1->header);      //write header
    fprintf(out,"%d %d\n",p1->W,p1->H);  //write width & height
    fprintf(out,"%d\n",p1->level);       //write color level
    for(i=0;i<p1->H;i++){                //write each pixel's RGB one by one
    	for(j=0;j<p1->W;j++){
            fprintf(out,"%c",p1->PX[j][i].r);
			fprintf(out,"%c",p1->PX[j][i].g);
			fprintf(out,"%c",p1->PX[j][i].b);
       	}
   	}
   	fclose(out);                         //close output file
}

IMG *PPMcvt(IMG *p1,IMG *ee,IMG *nthu){
	int i,j,c,NTHUloc[2]={},EEloc[2]={};//i,j looping index,b=black
	const int w=255;					//EEloc,NTHUloc store location info
										//w=white
	for(i=0;i<p1->H;i++){				//turn p1 to black & white
		for(j=0,c=0;j<p1->W;j++){
			c=p1->PX[j][i].r*0.2126+p1->PX[j][i].g*0.7152+p1->PX[j][i].b*0.0722;
			p1->PX[j][i].r=c;
			p1->PX[j][i].g=c;
			p1->PX[j][i].b=c;
		}
	}
	NTHUloc[width]=(p1->W-nthu->W)/2+1;	//find location for NTHU logo
	NTHUloc[height]=(p1->H-nthu->H)/2+1;//...
	for(i=0;i<nthu->H;i++){				//turn p1 to purple according to
		for(j=0;j<nthu->W;j++){			//the PX info of nthu
			if(nthu->PX[j][i].r!=w ||nthu->PX[j][i].g!=w ||nthu->PX[j][i].b!=w){
				p1->PX[(j+NTHUloc[width])][(i+NTHUloc[height])].r=w;
				p1->PX[(j+NTHUloc[width])][(i+NTHUloc[height])].b=w;
			}
		}
	}
	EEloc[width]=(p1->W)-(ee->W);		//find location for EE logo
	EEloc[height]=(p1->H)-(ee->H);		//...
	for(i=0;i<ee->H;i++){				//copy color info from EE logo to p1
		for(j=0;j<ee->W;j++){
			if(ee->PX[j][i].r!=w ||ee->PX[j][i].g!=w ||ee->PX[j][i].b!=w){
                p1->PX[j+EEloc[width]][i+EEloc[height]].r=ee->PX[j][i].r;
                p1->PX[j+EEloc[width]][i+EEloc[height]].g=ee->PX[j][i].g;
			    p1->PX[j+EEloc[width]][i+EEloc[height]].b=ee->PX[j][i].b;
            }
		}
	}
	return p1;
}

