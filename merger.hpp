#ifndef __H_MERGER__
#define __H_MERGER__

#include "defs.hpp"

class merge_kmers {
    private:
        strVec   infiles;
        ulongVec mat;
        
        void     merge();
        
    public:
                   merge_kmers( const strVec    & infilesl );
        void       get_matrix(        ulongVec  & matl     );
        ulongVec & get_matrix();
        void       read_matrix( const string    & prefix   );
        void       save_matrix( const string    & prefix   );
};

#endif