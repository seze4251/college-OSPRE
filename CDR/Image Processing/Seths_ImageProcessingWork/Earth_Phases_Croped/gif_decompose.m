function gif_decompose(gif_name, folder_name)
%Function to decompose a gif into all of its frames
%Inputs: 
%   - gif_name: name of the gif file
%   - folder_name: filename of folder where you want to save all the images
%
%Outputs: 
%   - all frames of the gif (saved in the location specified by filename)


allframedata = imread(gif_name,'gif', 'frames', 'all');
info = imfinfo(gif_name);

N = length(info);

for i = 1:N
    filename = [folder_name '\\' num2str(i) '.png'];
    imwrite(allframedata(:,:,1,i), info(i).ColorTable, filename);
end

end


