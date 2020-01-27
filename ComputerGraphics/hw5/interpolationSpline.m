[s0,s1,s2,s3] = cubic_spline(XBin',YBin');

for i = 1 : (n - 1)
    currX = round(XBin(i));
    nextX = round(XBin(i+1));
    xx = currX : 1 : nextX;
    repeatCount = size(xx,2);
    xi = repmat(XBin(i),1,repeatCount);
    yy = s0(i) + s1(i)*(xx-xi) + ... 
     s2(i)*(xx-xi).^2 + s3(i)*(xx - xi).^3;
 
 for j = 1 : repeatCount
     rectangle('Curvature',[0 0],'Position',[xx(j)-1,yy(j)-1,1,1],...
         'FaceColor',color);
 end
 
end