%we default the images and labels save in the same file 
seg_path='./human/data/ATR/train_images';
save_path='./human/data/ATR/resize_train_images/';
seg = dir(seg_path);
seg = seg(3:end);
for page=1:2:size(seg)
    img2 = imread([seg_path,GT_seg(page).name(1:end-4),'.png']);
    img = imread([seg_path,GT_seg(page).name(1:end-4),'.jpg']);
    label=X_label_resize(img2,[300,200]);   %X_label_resize uses to resize the png label;
    image=imresize(img,[300,200]);
    imwrite(label,[save_path,seg(page).name(1:end-4),'.png']);
    imwrite(image,[save_path,seg(page).name(1:end-4),'.jpg']);
end
