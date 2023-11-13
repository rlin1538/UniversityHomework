unsigned j = uf << 1 >> 24;
   unsigned w = uf << 9 >> 9;

   if (j == 0xff)
   {
      if (w)
         return 133955584;
      return uf;
   }
   unsigned a = 8388608;
   return uf+a;