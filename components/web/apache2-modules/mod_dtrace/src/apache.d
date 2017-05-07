provider apache {
    probe receive__request(uintptr_t);
    probe log__request(uintptr_t,string,string);
    probe create__child();
    probe accept__connection(uintptr_t);
    probe check__user__credentials(uintptr_t);
    probe check__access(uintptr_t);
    probe check__authorization(uintptr_t);
};

