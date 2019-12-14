  ! This is the Fortran wrapper for the ncglm library.

  ! Ed Hartnett 12/14/19

module ncglm

  contains
    function glm_read_dims() result(status)
      implicit none
      !    integer, intent(in) :: i ! input
      integer             :: status
      status = 0
    end function glm_read_dims
end module ncglm
