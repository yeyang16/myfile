%需要MATLAB 2016以上版本

clear;

%如有多个摄像头，可使用webcamlist命令选择摄像头
% camera=webcam; %connect to camera
% camera=webcam('Logitech HD Webcam C270'); %select one camera to connect
camera=webcam('Microsoft Camera Front'); %select one camera to connect

%选择预训练CNN模型（alexnet,googlenet,resnet等）
net=alexnet;%load neural network
inputSize = net.Layers(1).InputSize(1:2);%resize the image to the input size of the network


%Continuously display and classify images together with a histogram of the top five predictions.
h = figure;
h.Position(3) = 2*h.Position(3);
ax1 = subplot(1,2,1);
ax2 = subplot(1,2,2);
ax2.ActivePositionProperty = 'position';

keepRolling = true;
set(gcf,'CloseRequestFcn','keepRolling = false; closereq');

while keepRolling
    % Display and classify the image
    im = snapshot(camera);
    image(ax1,im)
    im = imresize(im,inputSize);
    [label,score] = classify(net,im);
    title(ax1,{char(label),num2str(max(score),2)});

    % Select the top five predictions
    [~,idx] = sort(score,'descend');
    idx = idx(5:-1:1);
    scoreTop = score(idx);
    classNames = net.Layers(end).ClassNames;
    classNamesTop = classNames(idx);

    % Plot the histogram
    barh(ax2,scoreTop)
    title(ax2,'Top 5')
    xlabel(ax2,'Probability')
    xlim(ax2,[0 1])
    yticklabels(ax2,classNamesTop)
    ax2.YAxisLocation = 'right';

    drawnow
end

