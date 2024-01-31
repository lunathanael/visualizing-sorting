#ifndef VIS_BACKEND_SORTER_HPP
#define VIS_BACKEND_SORTER_HPP

namespace vis::backend {
    template <typename Iterator> class Sorter {
    public:
        virtual Iterator begin() const = 0;
        virtual Iterator end() const = 0;
        virtual bool is_done() const = 0;
        virtual void next() = 0;
    };
}

#endif
