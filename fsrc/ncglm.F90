  ! This is the Fortran wrapper for the ncglm library.

  ! Ed Hartnett 12/14/19

module ncglm

  interface
     function glm_read_dims(ncid, nevent, ngroup, nflash) bind(c)
       use iso_c_binding
       integer(C_INT), value :: ncid
       integer(C_SIZE_T), intent(INOUT) :: nevent, ngroup, nflash
     end function glm_read_dims
  end interface

  interface
     function glm_read_event_arrays(ncid, nevent, event_id, time_offset, &
          lat, lon, energy, parent_group_id) bind(c)
       use iso_c_binding
       integer(C_INT), value :: ncid
       integer(C_SIZE_T), intent(INOUT) :: nevent
       integer(C_INT), intent(INOUT) :: event_id(*)
       real(C_FLOAT), intent(INOUT) :: time_offset(*)
       real(C_FLOAT), intent(INOUT) :: lat(*)
       real(C_FLOAT), intent(INOUT) :: lon(*)
       real(C_FLOAT), intent(INOUT) :: energy(*)
       integer(C_INT), intent(INOUT) :: parent_group_id(*)
     end function glm_read_event_arrays
  end interface

  ! interface
  !    function bind(c)
  !      use iso_c_binding
  !      integer(C_INT), value :: ncid
  !    end function
  ! end interface

  ! interface
  !    function bind(c)
  !      use iso_c_binding
  !      integer(C_INT), value :: ncid
  !    end function
  ! end interface

  contains
    function fglm_read_dims(ncid, nevent, ngroup, nflash) result(status)
      use iso_c_binding
      implicit none
      integer, intent(in) :: ncid
      integer, intent(out) :: nevent, ngroup, nflash
      integer*8 :: nevent8, ngroup8, nflash8
      integer :: status
      integer(C_INT) :: cstatus

      status = glm_read_dims(ncid, nevent8, ngroup8, nflash8)
      nevent = nevent8
      ngroup = ngroup8
      nflash = nflash8
    end function fglm_read_dims
end module ncglm
