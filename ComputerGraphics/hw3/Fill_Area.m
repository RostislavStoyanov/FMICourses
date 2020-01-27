
stack = [x,y];

while (~isempty(stack))
  
    newY = stack(end);
    stack(end) = [];
    
    newX = stack(end);
    stack(end) = [];
    
    if(M(newX, newY) == borderValue||M(newX,newY) == fillValue)
        continue;    
    end
   

   leftX = newX;
   rightX = newX;
   
   while (leftX > 1 && (M(leftX - 1, newY) ~= borderValue ))
     leftX = leftX - 1;
   end
   
   while ( rightX <= MaxX - 1 && (M(rightX + 1 , newY) ~= borderValue))
     rightX = rightX + 1;
   end
 
  if( newY >= 1 && newY <= MaxY && newX >= 1 && newX <= MaxX) 
    drawLine;
  end 
  
  oldBPoint = true;
  for currX = leftX : rightX
      if(newY+1>MaxX)
          break
      end
      if(M(currX,newY+1)~=borderValue)
          oldBPoint=true;
      end
      if(oldBPoint)
          oldBPoint=false;
          if(M(currX,newY+1)~=fillValue)
              stack(end+1)=currX;
              stack(end+1)=newY+1;
          end
      end
  end
      
      oldBPoint = true;
  for currX = leftX : rightX
      if(newY-1<0)
          break
      end
      if(M(currX,newY-1)~=borderValue)
          oldBPoint=true;
      end
      if(oldBPoint)
          oldBPoint=false;
          if(M(currX,newY-1)~=fillValue)
              stack(end+1)=currX;
              stack(end+1)=newY-1;
          end
      end
      
  end
   
end
