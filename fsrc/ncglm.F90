  ! This is the Fortran wrapper for the ncglm library.

  ! Ed Hartnett 12/14/19

module ncglm

  contains
    function glm_read_dims(ncid, nevent, ngroup, nflash) result(status)
      implicit none
      integer, intent(in) :: ncid
      integer, intent(out) :: nevent, ngroup, nflash
      integer             :: status
      nevent = 4578
      status = 0
    end function glm_read_dims
end module ncglm
