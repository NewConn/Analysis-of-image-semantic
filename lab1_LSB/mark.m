clc
clf
clear


pic=imread('photo.jpg'); %读图片
icon=imread('ico.jpg'); %读图标
icon_bit=im2bw(icon); %二值化
imwrite(icon_bit, 'icon_bit.jpg');
 
[m,n,k] = size(pic); %读图片像素点
[x,y,z] = size(icon); %读图标像素点
 
subplot(2,3,1);
imshow(pic);
title('(a) 原底图');
subplot(2,3,2);
imshow(icon);
title('(b) 原水印图');
subplot(2,3,3);
imshow(icon_bit);
title('(c) 二值化水印图');
 

pic_zero=pic;
std=254;
for i=1:m
for j=1:n  %遍历原图所有像素点      
pic_zero(i,j,3)=bitand(pic_zero(i,j,3),std); %和254进行二进制的按位与，将八位二进制数最后一位置零
    end;
end;
imwrite(pic_zero, 'pic_zero.jpg');
subplot(2,3,4);
imshow(pic_zero);
title('(d) 消0底图');
 
pic_add=pic_zero;
for i=1:x
    for j=1:y %对置零后图片进行图标大小的遍历
        bitset(pic_add(x,y,3),1,mark_bit(x,y));%将图标的数值填写到置零后图片的最后一位
    end;
end;
imwrite(pic_add, 'pic_add.jpg');
subplot(2,3,5);
imshow(pic_add);
title('(e) 加水印底图');
 
%%%%%%%提取水印 
pic_extract=icon_bit;
for i=1:x
    for j=1:y
        pic_extract(x,y)=0; %图片清零
        pic_extract(x,y)=bitget(pic_add(x,y,3),1);
    end;
end;
imwrite(pic_extract, 'pic_extract.jpg');
subplot(2,3,6);
imshow(pic_extract);
title('(f) 提取水印');
