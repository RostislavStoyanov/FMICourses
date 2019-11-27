function [outcode] = CalculateOutCode(x,y,XMin,XMax,YMin,YMax)
    outcode = 0;
    if(x < XMin)
        outcode = bitor(outcode,1);
    elseif(x > XMax)
         outcode = bitor(outcode,2);
    end
    
    if(y < YMin)
        outcode = bitor(outcode,4);
    elseif(y > YMax)
        outcode = bitor(outcode,8);
    end
end