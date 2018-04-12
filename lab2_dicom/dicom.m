clear all
clc

% read dicom image
dis = dir('F:\code\dicom\picture\*.dcm');
dis_length = length(dis);
im = zeros(400,400,dis_length);
for i = 1:dis_length
    path = strcat('F:\code\dicom\picture\',dis(i).name);
    im(:,:,i) =dicomread(path);
    %figure
    %imagesc(im{i})
    %hold on
end

pic_xoy = zeros(400);
for x = 1:400
    for y = 1:400
        value = 0;
        for i = 1:dis_length
            if im(x,y,i) > value
                value = im(x,y,i);
            end
        end
        pic_xoy(x,y) = value;
    end
end
figure
imagesc(pic_xoy);

pic_xoz = zeros(400,dis_length);
for x = 1:400
    for z = 1:dis_length
        value = 0;
        for i = 1:400
            if im(x,i,z) > value
                value = im(x,i,z);
            end
        end
        pic_xoz(x,z) = value;
    end
end
figure
imagesc(pic_xoz);

pic_yoz = zeros(400,dis_length);
for y = 1:400
    for z = 1:dis_length
        value = 0;
        for i = 1:400
            if im(i,y,z) > value
                value = im(i,y,z);
            end
        end
        pic_yoz(y,z) = value;
    end
end
figure
imagesc(pic_yoz);
