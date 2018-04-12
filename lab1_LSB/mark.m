clc
clf
clear

%%%%%%%���ˮӡ

pic=imread('photo.jpg');%��ͼƬ
icon=imread('ico.jpg');%��ͼ��
icon_bit=im2bw(icon); %��ֵ��
imwrite(icon_bit, 'icon_bit.jpg');

[m,n,k] = size(pic);%��ͼƬ���ص�
[x,y,z] = size(icon);%��ͼ�����ص�

subplot(2,3,1);
imshow(pic);
title('(a)ԭͼ');
subplot(2,3,2);
imshow(icon);
title('(b)ԭͼ��');
subplot(2,3,3);
imshow(icon_bit);
title('(c)��ֵ��ͼ��');


pic_zero=pic;
std=254;
for i=1:m
    for j=1:n  %����ԭͼ�������ص�
        pic_zero(i,j,3)=bitand(pic_zero(i,j,3),std); %��254���ж����Ƶİ�λ�룬����λ�����������һλ����
    end;
end;
imwrite(pic_zero, 'pic_zero.jpg');
subplot(2,3,4);
imshow(pic_zero);
title('(d)ԭͼ����');

pic_add=pic_zero;
for i=1:x
    for j=1:y %�������ͼƬ����ͼ���С�ı���
        pic_add(x,y,3)=icon_bit(x,y);%��ͼ�����ֵ��д�������ͼƬ�����һλ
    end;
end;
imwrite(pic_add, 'pic_add.jpg');
subplot(2,3,5);
imshow(pic_add);
title('(e)��ͼ����ͼƬ');

%%%%%%%��ȡˮӡ

pic_extract=icon_bit;
for i=1:x
    for j=1:y
        pic_extract(x,y)=0;%ͼƬ����
        pic_extract(x,y)=pic_add(x,y,3); %����ˮӡ��ͼƬ�����һλ����һ�ſհ�ͼ
    end;
end;
imwrite(pic_extract, 'pic_extract.jpg');
subplot(2,3,6);
imshow(pic_extract);
title('(f)��ȡ��ͼ��');
        