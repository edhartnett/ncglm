  ! This is the Fortran wrapper for the ncglm library.

  ! Ed Hartnett 12/14/19

module ncglm

  interface
     function glm_read_dims(ncid, nevent, ngroup, nflash) bind(c)
       use iso_c_binding
       integer(C_INT), value :: ncid
       integer(C_INT), intent(INOUT) :: nevent, ngroup, nflash
     end function glm_read_dims
  end interface

  contains
    function fglm_read_dims(ncid, nevent, ngroup, nflash) result(status)
      use iso_c_binding
      implicit none
      integer, intent(in) :: ncid
      integer, intent(out) :: nevent, ngroup, nflash
      integer :: status
      integer(C_INT) :: cstatus

      nevent = 4578
      status = glm_read_dims(ncid, nevent, ngroup, nflash)
    end function fglm_read_dims
end module ncglm
