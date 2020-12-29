#ifndef __TYPE_TRAITS_H
#define __TYPE_TRAITS_H

struct __true_type { };
struct __false_type { };

template <class T>
struct __type_traits
{
    using this_dummy_member_must_be_first = __true_type;
    using has_trivial_default_constructor = __false_type;
    using has_trivial_copy_constructor = __false_type;
    using has_trivial_assignment_operator = __false_type;
    using has_trivial_destructor = __false_type;
    using is_POD_type = __false_type;
};

#endif