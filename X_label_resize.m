function [ output_label ] = X_label_resize( input_label,resizetarget )
%LABEL_TRANS Summary of this function goes here
%   Detailed explanation goes here
input_label = uint8(input_label);
annosize = size(input_label);
labellist = unique(input_label);
highest_label = max(labellist);
labelmask_bef = zeros(annosize(1),annosize(2),highest_label + 1);
labelmask_aft = zeros(resizetarget(1),resizetarget(2),highest_label + 1);
for j = 0:highest_label
    if(sum(labellist==j)>0)
        labelmask_bef(:,:,j + 1) = uint8(input_label == j);
	    labelmask_aft(:,:,j + 1) = imresize(labelmask_bef(:,:,j + 1),resizetarget);
    else
        labelmask_bef(:,:,j + 1) = zeros(annosize);
        labelmask_aft(:,:,j + 1) = zeros(resizetarget);
    end
end
[dump,output_label] = max(labelmask_aft,[],3);
output_label = uint8(output_label - 1);
end
